#include "gl.h"
#include <iostream>

using namespace std;

XGLAPI void GLAPIENTRY glEnd(void)
{
    cout << "glEnd()" << endl;
}

XGLAPI void GLAPIENTRY glPointSize( GLfloat size ) { 
    cout << "glPointSize(" << size << ")" << endl;
}

XGLAPI void GLAPIENTRY glPolygonMode( GLenum face, GLenum mode ) { 
    cout << "glPolygonMode(" << face << ", " << mode << ")" << endl;
}

XGLAPI void GLAPIENTRY glGetDoublev( GLenum pname, GLdouble *params ) { 
    cout << "glGetDoublev(" << pname << ", " << params << ")" << endl;
}

XGLAPI void GLAPIENTRY glPushAttrib( GLbitfield mask ) { 
    cout << "glPushAttrib(" << mask << ")" << endl;
}

XGLAPI void GLAPIENTRY glPopAttrib( void ) { 
    cout << "glPopAttrib()" << endl;
}

XGLAPI void GLAPIENTRY glPushMatrix( void ) { 
    cout << "glPushMatrix()" << endl;
}

XGLAPI void GLAPIENTRY glPopMatrix( void ) { 
    cout << "glPopMatrix()" << endl;
}

XGLAPI void GLAPIENTRY glMultMatrixf( const GLfloat *m ) { 
    cout << "glMultMatrixf(" << m << ")" << endl;
}

XGLAPI void GLAPIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z ) {
    cout << "glRotatef(" << angle << ", " << x << ", " << y << ", " << z << ")" << endl;
}

XGLAPI void GLAPIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z ) { 
    cout << "glTranslatef(" << x << ", " << y << ", " << z << ")" << endl;
}

XGLAPI void GLAPIENTRY glDeleteLists( GLuint list, GLsizei range ) { 
    cout << "glDeleteLists(" << list << ", " << range << ")" << endl;
}

XGLAPI GLuint GLAPIENTRY glGenLists( GLsizei range ) { 
    cout << "glGenLists(" << range << ")" << endl;
    return 0;
}

XGLAPI void GLAPIENTRY glNewList( GLuint list, GLenum mode ) { 
    cout << "glNewList(" << list << ", " << mode << ")" << endl;
}

XGLAPI void GLAPIENTRY glEndList( void ) { 
    cout << "glEndList()" << endl;
}

XGLAPI void GLAPIENTRY glCallList( GLuint list ) { 
    cout << "glCallList(" << list << ")" << endl;
}

XGLAPI void GLAPIENTRY glCallLists( GLsizei n, GLenum type, const GLvoid *lists ) {
    cout << "glCallLists(" << n << ", " << type << ", " << lists << ")" << endl;
}

XGLAPI void GLAPIENTRY glVertex2f( GLfloat x, GLfloat y ) { 
    cout << "glVertex2f(" << x << ", " << y << ")" << endl;
}

XGLAPI void GLAPIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z ) { 
    cout << "glVertex3f(" << x << ", " << y << ", " << z << ")" << endl;
}

XGLAPI void GLAPIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz ) { 
    cout << "glNormal3f(" << nx << ", " << ny << ", " << nz << ")" << endl;
}

XGLAPI void GLAPIENTRY glColor3d( GLdouble red, GLdouble green, GLdouble blue ) { 
    cout << "glColor3d(" << red << ", " << green << ", " << blue << ")" << endl;
}

XGLAPI void GLAPIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue ) { 
    cout << "glColor3f(" << red << ", " << green << ", " << blue << ")" << endl;
}

XGLAPI void GLAPIENTRY glColor3i( GLint red, GLint green, GLint blue ) { 
    cout << "glColor3i(" << red << ", " << green << ", " << blue << ")" << endl;
}

XGLAPI void GLAPIENTRY glTexCoord3f( GLfloat s, GLfloat t, GLfloat r ) { 
    cout << "glTexCoord3f(" << s << ", " << t << ", " << r << ")" << endl;
}

XGLAPI void GLAPIENTRY glRasterPos2f( GLfloat x, GLfloat y ) { 
    cout << "glRasterPos2f(" << x << ", " << y << ")" << endl;
}

XGLAPI void GLAPIENTRY glRasterPos3f( GLfloat x, GLfloat y, GLfloat z ) { 
    cout << "glRasterPos3f(" << x << ", " << y << ", " << z << ")" << endl;
}

XGLAPI void GLAPIENTRY glShadeModel( GLenum mode ) { 
    cout << "glShadeModel(" << mode << ")" << endl;
}

XGLAPI void GLAPIENTRY glLightf( GLenum light, GLenum pname, GLfloat param ) { 
    cout << "glLightf(" << light << ", " << pname << ", " << param << ")" << endl;
}

XGLAPI void GLAPIENTRY glLightfv( GLenum light, GLenum pname,const GLfloat *params ) {
    cout << "glLightfv(" << light << ", " << pname << ", " << params << ")" << endl;
}

XGLAPI void GLAPIENTRY glMaterialf( GLenum face, GLenum pname, GLfloat param ) { 
    cout << "glMaterialf(" << face << ", " << pname << ", " << param << ")" << endl;
}

XGLAPI void GLAPIENTRY glMaterialfv( GLenum face, GLenum pname, const GLfloat *params ) { 
    cout << "glMaterialfv(" << face << ", " << pname << ", " << params << ")" << endl;
}

XGLAPI void GLAPIENTRY glPixelZoom( GLfloat xfactor, GLfloat yfactor ) { 
    cout << "glPixelZoom(" << xfactor << ", " << yfactor << ")" << endl;
}

XGLAPI void GLAPIENTRY glTexEnvf( GLenum target, GLenum pname, GLfloat param ) { 
    cout << "glTexEnvf(" << target << ", " << pname << ", " << param << ")" << endl;
}
