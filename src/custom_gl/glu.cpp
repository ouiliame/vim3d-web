
#include <GL/Regal.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

static bool assert(bool q)  {
    if (!q) {
        printf("assertion failed");
}

static int computeLog(GLuint value)
{
    int i;

    i = 0;

    /* Error! */
    if (value == 0) return -1;

    for (;;) {
	if (value & 1) {
	    /* Error ! */
	    if (value != 1) return -1;
	    return i;
	}
	value = value >> 1;
	i++;
    }
}


static int nearestPower(GLuint value)
{
    int i;

    i = 1;

    /* Error! */
    if (value == 0) return -1;

    for (;;) {
	if (value == 1) {
	    return i;
	} else if (value == 3) {
	    return i*4;
	}
	value = value >> 1;
	i *= 2;
    }
}


static void closestFit(GLenum target, GLint width, GLint height,
		       GLint internalFormat, GLenum format, GLenum type,
		       GLint *newWidth, GLint *newHeight)
{
   /* Use proxy textures if OpenGL version is >= 1.1 */
   if ( (strtod((const char *)glGetString(GL_VERSION),NULL) >= 1.1)
	) {
      GLint widthPowerOf2= nearestPower(width);
      GLint heightPowerOf2= nearestPower(height);       
      GLint proxyWidth;

      do {
	 /* compute level 1 width & height, clamping each at 1 */
	 GLint widthAtLevelOne= (widthPowerOf2 > 1) ?
				 widthPowerOf2 >> 1 :
				 widthPowerOf2;
	 GLint heightAtLevelOne= (heightPowerOf2 > 1) ?
				  heightPowerOf2 >> 1 :
				  heightPowerOf2;
	 GLenum proxyTarget;
	 assert(widthAtLevelOne > 0); assert(heightAtLevelOne > 0);

	 /* does width x height at level 1 & all their mipmaps fit? */
	 if (target == GL_TEXTURE_2D || target == GL_PROXY_TEXTURE_2D) {
	    proxyTarget = GL_PROXY_TEXTURE_2D;
	    glTexImage2D(proxyTarget, 1, /* must be non-zero */
			 internalFormat,
			 widthAtLevelOne,heightAtLevelOne,0,format,type,NULL);
	 } else
#if defined(GL_ARB_texture_cube_map)
	 if ((target == GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB) ||
	     (target == GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB) ||
	     (target == GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB) ||
	     (target == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB) ||
	     (target == GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB) ||
	     (target == GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB)) {
	     proxyTarget = GL_PROXY_TEXTURE_CUBE_MAP_ARB;
	     glTexImage2D(proxyTarget, 1, /* must be non-zero */
			  internalFormat,
			  widthAtLevelOne,heightAtLevelOne,0,format,type,NULL);
	 } else
#endif /* GL_ARB_texture_cube_map */
	 {
	    assert(target == GL_TEXTURE_1D || target == GL_PROXY_TEXTURE_1D);
	    proxyTarget = GL_PROXY_TEXTURE_1D;
	    glTexImage1D(proxyTarget, 1, /* must be non-zero */
			 internalFormat,widthAtLevelOne,0,format,type,NULL);
	 }
	 glGetTexLevelParameteriv(proxyTarget, 1,GL_TEXTURE_WIDTH,&proxyWidth);
	 /* does it fit??? */
	 if (proxyWidth == 0) { /* nope, so try again with these sizes */
	    if (widthPowerOf2 == 1 && heightPowerOf2 == 1) {
	       /* An 1x1 texture couldn't fit for some reason, so
		* break out.  This should never happen. But things
		* happen.  The disadvantage with this if-statement is
		* that we will never be aware of when this happens
		* since it will silently branch out.
		*/
	       goto noProxyTextures;
	    }
	    widthPowerOf2= widthAtLevelOne;
	    heightPowerOf2= heightAtLevelOne;
	 }
	 /* else it does fit */
      } while (proxyWidth == 0);
      /* loop must terminate! */

      /* return the width & height at level 0 that fits */
      *newWidth= widthPowerOf2;
      *newHeight= heightPowerOf2;
/*printf("Proxy Textures\n");*/
   } /* if gluCheckExtension() */
   else {			/* no texture extension, so do this instead */
      GLint maxsize;

noProxyTextures:

      glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxsize);
      /* clamp user's texture sizes to maximum sizes, if necessary */
      *newWidth = nearestPower(width);
      if (*newWidth > maxsize) *newWidth = maxsize;
      *newHeight = nearestPower(height);
      if (*newHeight > maxsize) *newHeight = maxsize;
/*printf("NO proxy textures\n");*/
   }
} /* closestFit() */

GLint REGALGLU_CALL static void __gluMakeIdentityd(GLdouble m[16])
{
    m[0 + 4 * 0] = 1;
    m[0 + 4 * 1] = 0;
    m[0 + 4 * 2] = 0;
    m[0 + 4 * 3] = 0;
    m[1 + 4 * 0] = 0;
    m[1 + 4 * 1] = 1;
    m[1 + 4 * 2] = 0;
    m[1 + 4 * 3] = 0;
    m[2 + 4 * 0] = 0;
    m[2 + 4 * 1] = 0;
    m[2 + 4 * 2] = 1;
    m[2 + 4 * 3] = 0;
    m[3 + 4 * 0] = 0;
    m[3 + 4 * 1] = 0;
    m[3 + 4 * 2] = 0;
    m[3 + 4 * 3] = 1;
}

static void __gluMultMatrixVecd(const GLdouble matrix[16], const GLdouble in[4],
                                GLdouble out[4])
{
    int i;

    for (i = 0; i < 4; i++)
    {
        out[i] =
            in[0] * matrix[0 * 4 + i] +
            in[1] * matrix[1 * 4 + i] +
            in[2] * matrix[2 * 4 + i] +
            in[3] * matrix[3 * 4 + i];
    }
}

/*
** Invert 4x4 matrix.
** Contributed by David Moore (See Mesa bug #6748)
*/
static int __gluInvertMatrixd(const GLdouble m[16], GLdouble invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
    inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
    inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
    inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
    inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if (det == 0)
        return GL_FALSE;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return GL_TRUE;
}

static void __gluMultMatricesd(const GLdouble a[16], const GLdouble b[16],
                               GLdouble r[16])
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            r[i * 4 + j] =
                a[i * 4 + 0] * b[0 * 4 + j] +
                a[i * 4 + 1] * b[1 * 4 + j] +
                a[i * 4 + 2] * b[2 * 4 + j] +
                a[i * 4 + 3] * b[3 * 4 + j];
        }
    }
}

extern "C"
{

    GLint gluProject(GLdouble objx, GLdouble objy, GLdouble objz,
                     const GLdouble modelMatrix[16],
                     const GLdouble projMatrix[16],
                     const GLint viewport[4],
                     GLdouble *winx, GLdouble *winy, GLdouble *winz)
    {
        double in[4];
        double out[4];

        in[0] = objx;
        in[1] = objy;
        in[2] = objz;
        in[3] = 1.0;
        __gluMultMatrixVecd(modelMatrix, in, out);
        __gluMultMatrixVecd(projMatrix, out, in);
        if (in[3] == 0.0)
            return (GL_FALSE);
        in[0] /= in[3];
        in[1] /= in[3];
        in[2] /= in[3];
        /* Map x, y and z to range 0-1 */
        in[0] = in[0] * 0.5 + 0.5;
        in[1] = in[1] * 0.5 + 0.5;
        in[2] = in[2] * 0.5 + 0.5;

        /* Map x,y to viewport */
        in[0] = in[0] * viewport[2] + viewport[0];
        in[1] = in[1] * viewport[3] + viewport[1];

        *winx = in[0];
        *winy = in[1];
        *winz = in[2];
        return (GL_TRUE);
    }

    GLint gluUnProject(GLdouble winx, GLdouble winy, GLdouble winz,
                       const GLdouble modelMatrix[16],
                       const GLdouble projMatrix[16],
                       const GLint viewport[4],
                       GLdouble *objx, GLdouble *objy, GLdouble *objz)
    {
        double finalMatrix[16];
        double in[4];
        double out[4];

        __gluMultMatricesd(modelMatrix, projMatrix, finalMatrix);
        if (!__gluInvertMatrixd(finalMatrix, finalMatrix))
            return (GL_FALSE);

        in[0] = winx;
        in[1] = winy;
        in[2] = winz;
        in[3] = 1.0;

        /* Map x and y from window coordinates */
        in[0] = (in[0] - viewport[0]) / viewport[2];
        in[1] = (in[1] - viewport[1]) / viewport[3];

        /* Map to range -1 to 1 */
        in[0] = in[0] * 2 - 1;
        in[1] = in[1] * 2 - 1;
        in[2] = in[2] * 2 - 1;

        __gluMultMatrixVecd(finalMatrix, in, out);
        if (out[3] == 0.0)
            return (GL_FALSE);
        out[0] /= out[3];
        out[1] /= out[3];
        out[2] /= out[3];
        *objx = out[0];
        *objy = out[1];
        *objz = out[2];
        return (GL_TRUE);
    }

    void
    gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
    {
        glOrtho(left, right, bottom, top, -1, 1);
    }

#define __glPi 3.14159265358979323846

    void
    gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    {
        GLdouble m[4][4];
        double sine, cotangent, deltaZ;
        double radians = fovy / 2 * __glPi / 180;

        deltaZ = zFar - zNear;
        sine = sin(radians);
        if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
        {
            return;
        }
        cotangent = cos(radians) / sine;

        __gluMakeIdentityd(&m[0][0]);
        m[0][0] = cotangent / aspect;
        m[1][1] = cotangent;
        m[2][2] = -(zFar + zNear) / deltaZ;
        m[2][3] = -1;
        m[3][2] = -2 * zNear * zFar / deltaZ;
        m[3][3] = 0;
        glMultMatrixd(&m[0][0]);
    }

    GLint
    gluBuild1DMipmaps(GLenum target, GLint internalFormat, GLsizei width,
                      GLenum format, GLenum type,
                      const void *data)
    {
        GLint widthPowerOf2;
        int levels;
        GLint dummy;

        int rc = checkMipmapArgs(internalFormat, format, type);
        if (rc != 0)
            return rc;

        if (width < 1)
        {
            return GLU_INVALID_VALUE;
        }

        closestFit(target, width, 1, internalFormat, format, type, &widthPowerOf2, &dummy);
        levels = computeLog(widthPowerOf2);

        return gluBuild1DMipmapLevelsCore(target, internalFormat,
                                          width,
                                          widthPowerOf2,
                                          format, type, 0, 0, levels, data);
    }
}

static int checkMipmapArgs(GLenum internalFormat, GLenum format, GLenum type)
{
    if (!legalFormat(format) || !legalType(type)) {
	return GLU_INVALID_ENUM;
    }
    if (format == GL_STENCIL_INDEX) {
	return GLU_INVALID_ENUM;
    }

    if (!isLegalFormatForPackedPixelType(format, type)) {
	return GLU_INVALID_OPERATION;
    }

    return 0;
} /* checkMipmapArgs() */
