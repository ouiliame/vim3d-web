#include "freeglut_std.h"
#include <iostream>

using namespace std;

XFGAPI void    FGAPIENTRY glutBitmapCharacter( void* font, int character ) {
    cout << "glutBitmapCharacter(" << font << ", " << character << ")" << endl;
}

XFGAPI void    FGAPIENTRY glutSolidSphere( GLdouble radius, GLint slices, GLint stacks ) {
    cout << "glutSolidSphere(" << radius << ", " << slices << ", " << stacks << ")" << endl;
}

XFGAPI void    FGAPIENTRY glutWireCone( GLdouble base, GLdouble height, GLint slices, GLint stacks ) {
    cout << "glutWireCone(" << base << ", " << height << ", " << slices << ", " << stacks << ")" << endl;
}

XFGAPI void    FGAPIENTRY glutSolidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks ) {
    cout << "glutSolidCone(" << base << ", " << height << ", " << slices << ", " << stacks << ")" << endl;
}