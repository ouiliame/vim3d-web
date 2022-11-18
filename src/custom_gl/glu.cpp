#include <GL/glu.h>
#include <iostream>

using namespace std;

GLAPI GLint GLAPIENTRY gluBuild1DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data) {
    cout << "gluBuild1DMipmaps(" << target << ", " << internalFormat << ", " << width << ", " << format << ", " << type << ", " << data << ")" << endl;
    return 0; 
}

GLAPI GLint GLAPIENTRY gluBuild2DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data) {
    cout << "gluBuild2DMipmaps(" << target << ", " << internalFormat << ", " << width << ", " << height << ", " << format << ", " << type << ", " << data << ")" << endl;
    return 0; 
}

GLAPI void GLAPIENTRY gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
    cout << "gluOrtho2D(" << left << ", " << right << ", " << bottom << ", " << top << ")" << endl;
}

GLAPI void GLAPIENTRY gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    cout << "gluPerspective(" << fovy << ", " << aspect << ", " << zNear << ", " << zFar << ")" << endl;
}

GLAPI GLint GLAPIENTRY gluUnProject (GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ) {
    cout << "gluUnProject(" << winX << ", " << winY << ", " << winZ << ", " << model << ", " << proj << ", " << view << ", " << objX << ", " << objY << ", " << objZ << ")" << endl;
    return 0;
}