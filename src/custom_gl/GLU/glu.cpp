#include <GL/glu.h>
#include <iostream>
#include <math.h>

using namespace std;

// GLAPI GLint GLAPIENTRY gluBuild1DMipmaps (GLenum target, GLint internalFormat, GLsizei width,
// GLenum format, GLenum type, const void *data) {
//     cout << "gluBuild1DMipmaps(" << target << ", " << internalFormat << ", " << width << ", " <<
//     format << ", " << type << ", " << data << ")" << endl; return 0;
// }

extern "C" GLint GLAPIENTRY
mgluBuild2DMipmaps(GLenum target,
                   GLint internalFormat,
                   GLsizei width,
                   GLsizei height,
                   GLenum format,
                   GLenum type,
                   const void* data)
{
    return gluBuild2DMipmaps(target, internalFormat, width, height, format, type, data);
}

extern "C" void GLAPIENTRY
mgluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    return glOrtho(left, right, bottom, top, -1, 1);
}

extern "C" void GLAPIENTRY
mgluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    // fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan(fovy / 360 * pi) * zNear;
    fW = fH * aspect;

    return glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

extern "C" GLAPI GLint GLAPIENTRY
mgluUnProject(GLdouble winX,
              GLdouble winY,
              GLdouble winZ,
              const GLdouble* model,
              const GLdouble* proj,
              const GLint* view,
              GLdouble* objX,
              GLdouble* objY,
              GLdouble* objZ)
{
    return gluUnProject(winX, winY, winZ, model, proj, view, objX, objY, objZ);
}