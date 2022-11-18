# vim3d: Browser Edition

**NOTE: CURRENTLY A WORK IN PROGRESS!**

We're trying to bring [vim3d](https://vim3d.com) to the web!

This repository contains the web port of Dan Lynch's [vim3d](https://github.com/pyramation/vim3d), forked off the original repo. 

## Porting Strategy

Since vim3d was written with C++ and OpenGL, our plan is to use [Emscripten](https://emscripten.org) to compile it to WebAssembly and run it in the browser.

However, we will need to resolve a couple challenges:

- **Unsupported OpenGL functions**

  The original code uses some OpenGL functions which aren't available on Emscripten, which only supports the OpenGL ES subset.


## Tasks

- [x] replace build system with CMake

## Development

### Requirements

To build this project, you will need to install the [Emscripten toolchain](https://emscripten.org/docs/getting_started/downloads.html).

Once installed, you should be able to use `emcc`.  

```bash
$ emcc -v

emcc (Emscripten gcc/clang-like replacement + linker emulating GNU ld) 3.1.24-git
clang version 16.0.0 (https://github.com/llvm/llvm-project.git 277c382760bf9575cfa2eac73d5ad1db91466d3f)
Target: wasm32-unknown-emscripten
Thread model: posix
InstalledDir: /opt/homebrew/Cellar/emscripten/3.1.24/libexec/llvm/bin
```

Make sure you have the following on your system:

- `cmake`
- `make`

### Building the project

## Build

```bash
make build
```

## Run

This runs with built project with `emrun`. Be sure to redefine the browser to your preference in the Makefile.

```bash
make run
```

## Implementing Unsupported Symbols

We modify `src/OpenGLinc.h` to use local headers in `src/custom_gl/` forked from [emscripten-core](https://github.com/emscripten-core/emscripten).

- `<GL/gl.h>` -> `"custom_gl/gl.h"`
- `<GL/glu.h>` -> `"custom_gl/glu.h"`
- `<GL/glut.h>` -> `"custom_gl/glut.h"` (actual stuff is imported from `freeglut_std.h`.

First we need to redefine part of headers.

### `gl.h`

Implementation is in `src/custom_gl/gl.cpp`.

Define `XGLAPI` to demarcate stuff we'll override.

Then, we tagged the following:

```c
...
#define XGLAPI /* nothing */

XGLAPI void GLAPIENTRY glPointSize( GLfloat size );
XGLAPI void GLAPIENTRY glPolygonMode( GLenum face, GLenum mode );
XGLAPI void GLAPIENTRY glGetDoublev( GLenum pname, GLdouble *params );
XGLAPI void GLAPIENTRY glPushAttrib( GLbitfield mask );
XGLAPI void GLAPIENTRY glPopAttrib( void );
XGLAPI void GLAPIENTRY glPushMatrix( void );
XGLAPI void GLAPIENTRY glPopMatrix( void );
XGLAPI void GLAPIENTRY glMultMatrixf( const GLfloat *m );
XGLAPI void GLAPIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
XGLAPI void GLAPIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z );
XGLAPI void GLAPIENTRY glDeleteLists( GLuint list, GLsizei range );
XGLAPI GLuint GLAPIENTRY glGenLists( GLsizei range );
XGLAPI void GLAPIENTRY glNewList( GLuint list, GLenum mode );
XGLAPI void GLAPIENTRY glEndList( void );
XGLAPI void GLAPIENTRY glCallList( GLuint list );
XGLAPI void GLAPIENTRY glCallLists( GLsizei n, GLenum type, const GLvoid *lists );
XGLAPI void GLAPIENTRY glEnd( void );
XGLAPI void GLAPIENTRY glVertex2f( GLfloat x, GLfloat y );
XGLAPI void GLAPIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z );
XGLAPI void GLAPIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz );
XGLAPI void GLAPIENTRY glColor3d( GLdouble red, GLdouble green, GLdouble blue );
XGLAPI void GLAPIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue );
XGLAPI void GLAPIENTRY glColor3i( GLint red, GLint green, GLint blue );
XGLAPI void GLAPIENTRY glTexCoord3f( GLfloat s, GLfloat t, GLfloat r );
XGLAPI void GLAPIENTRY glRasterPos2f( GLfloat x, GLfloat y );
XGLAPI void GLAPIENTRY glRasterPos3f( GLfloat x, GLfloat y, GLfloat z );
XGLAPI void GLAPIENTRY glShadeModel( GLenum mode );
XGLAPI void GLAPIENTRY glLightf( GLenum light, GLenum pname, GLfloat param );
XGLAPI void GLAPIENTRY glLightfv( GLenum light, GLenum pname, const GLfloat *params );
XGLAPI void GLAPIENTRY glMaterialf( GLenum face, GLenum pname, GLfloat param );
XGLAPI void GLAPIENTRY glMaterialfv( GLenum face, GLenum pname, const GLfloat *params );
XGLAPI void GLAPIENTRY glPixelZoom( GLfloat xfactor, GLfloat yfactor );
XGLAPI void GLAPIENTRY glTexEnvf( GLenum target, GLenum pname, GLfloat param );

```

### `glu.h`

Implementation is in `src/custom_gl/glu.cpp`.

```c
...
#define XGLAPI /* nothing */

XGLAPI GLint GLAPIENTRY gluBuild1DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data);
XGLAPI GLint GLAPIENTRY gluBuild2DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data);
XGLAPI void GLAPIENTRY gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
XGLAPI void GLAPIENTRY gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
XGLAPI GLint GLAPIENTRY gluUnProject (GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ);
```

### `glut.h` (actually `freeglut_std.h`)

Implementation is in `src/custom_gl/freeglut_std.cpp`.

Use `XFGAPI` to demarcate stuff we'll be overriding.

```c
...
#define XFGAPI /* nothing */

XFGAPI void    FGAPIENTRY glutBitmapCharacter( void* font, int character );
XFGAPI void    FGAPIENTRY glutSolidSphere( GLdouble radius, GLint slices, GLint stacks );
XFGAPI void    FGAPIENTRY glutWireCone( GLdouble base, GLdouble height, GLint slices, GLint stacks );
XFGAPI void    FGAPIENTRY glutSolidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks );
```