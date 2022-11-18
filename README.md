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

## Get the repo

```bash
git clone https://github.com/ouiliame/vim3d-web
cd vim3d-web
```

We use `gl4es` which is a submodule. After the above, do:

```bash
git submodule update --init --recursive
```

Then build the `libGL` library.

```bash 
(cd gl4es && rm -rf build; mkdir build; cd build; emcmake cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DNOX11=ON -DNOEGL=ON -DSTATICLIB=ON; make)
```

Now you should have `gl4es/lib/libGL.a` in your project, which is required.

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

### Using `gl4es`

We use `gl4es` instead of the default Emscripten bundled `libGL`.

Notice the following:

#### src/OpenGLinc.h

```cpp
#ifndef OPENGLINC_H
#define OPENGLINC_H

#include <gl4esinit.h> // include extra
#include <GL/gl.h>
#include <GL/glu.h>

#include "custom_gl/glut.h"

#endif
```
#### src/main.cpp

```cpp
#include "Scene.h"

int main(int argc, char* argv[]) {
    initialize_gl4es(); // need to call this before any GL calls!
    Scene *scene = new Scene();
    scene->go(argc, argv);
    delete scene;
    return 0;
}

```

### Providing unsupported GLUT functions

We modify `src/OpenGLinc.h` to use local headers in `src/custom_gl/` forked from [emscripten-core](https://github.com/emscripten-core/emscripten).

- `<GL/glut.h>` -> `"custom_gl/glut.h"` (actual stuff is imported from `freeglut_std.h`.

The following functions need to be provided, as they aren't included:

#### src/custom_gl/glu.cpp

```cpp
GLAPI GLint GLAPIENTRY gluBuild1DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data);

GLAPI GLint GLAPIENTRY gluBuild2DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data); 


GLAPI void GLAPIENTRY gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);

GLAPI void GLAPIENTRY gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

GLAPI GLint GLAPIENTRY gluUnProject (GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ);
```

#### src/freeglut_std.<h/cpp>

```cpp
FGAPI void FGAPIENTRY glutBitmapCharacter(void *_font, int character);

FGAPI void FGAPIENTRY glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);

FGAPI void FGAPIENTRY glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);

FGAPI void FGAPIENTRY glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
```