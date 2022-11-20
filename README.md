# vim3d.js - Emscripten port

This repository contains the web port of Dan Lynch's [vim3d](https://github.com/pyramation/vim3d), forked off the original repo. I made some changes to the original code to make it work with Emscripten described in the [porting details](#porting) part of this document.

## Demo

You can play with the demo [here](https://ouiliame.github.io/vim3d.js/).

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

## Building the project

First, clone this repository.

```bash
git clone https://github.com/ouiliame/vim3d.js.git
cd vim3d.js
```

Then build:

```bash
make build
```

## Run

This runs with built project with `emrun`. Be sure to redefine the browser to your preference in the Makefile.

```bash
make run
```

# Notes on Porting

The following are notes about the changes I made to the original code to make it work with Emscripten.

## CMake

Originally, this project was built with a Makefile. I changed it to use CMake, the modern choice of build system for C++ projects, as the build was getting more complex.

I also added a `Makefile` at the root to invoke CMake and build the project.

## OpenGL

The original code uses an outdated style of writing OpenGL which is not supported by Emscripten, which supports only the WebGL subject of the OpenGL ES 2.0 specification.

I decided to use the following libraries to make the port possible:

In `src/OpenGLinc.h`:

```c
#ifndef OPENGLINC_H
#define OPENGLINC_H

// remove platform checks, we're on Emscripten
#include <GL/gl.h>
#include <GL/glu.h>

// use my fixed GLUT headers
#include "custom_gl/freeglut/freeglut_std.h"

#endif
```

### 1. GL4ES for unsupported OpenGL functions

I used [GL4ES](https://github.com/ptitSeb/gl4es), which maps OpenGL 1.1 calls to OpenGL ES 2.0 calls, to make the code work. (Emscripten only supports the WebGL 2.0 API, which is a subset of OpenGL ES 3.0. [^1]

[1]: See [this](https://emscripten.org/docs/porting/guidelines/function_pointer_issues.html#opengl-and-webgl) for more details.

### 2. GLUES for missing GLU functions

The original code uses several GLU functions which are not supported by Emscripten. Luckily, these are just basic math-related operations that use GL calls described by the GLU specification.

I simply included source files from [GLUES](https://github.com/ptitSeb/glues) in the project, located in the `src/custom_gl/glues` directory.

#### `src/OpenGLinc.h`

```cpp
extern "C" GLint GLAPIENTRY
mgluBuild2DMipmaps(GLenum target,
                   GLint internalFormat,
                   GLsizei width,
                   GLsizei height,
                   GLenum format,
                   GLenum type,
                   const void* data);

extern "C" void GLAPIENTRY
mgluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);

extern "C" void GLAPIENTRY
mgluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

extern "C" GLAPI GLint GLAPIENTRY
mgluUnProject(GLdouble winX,
              GLdouble winY,
              GLdouble winZ,
              const GLdouble* model,
              const GLdouble* proj,
              const GLint* view,
              GLdouble* objX,
              GLdouble* objY,
              GLdouble* objZ);
```

### 3. FreeGLUT for missing GLUT functions

The original code uses GLUT to do various things, such as creating a window, handling keyboard events, etc.

However, Emscripten's GLUT implementation is incomplete and does not support the functions used in the original code.
Luckily, GLUT is not used for much in the original code, so I was able to just implement the missing functions by referencing the code from [FreeGLUT](https://github.com/FreeGLUTProject/freeglut).

### Modifications to Emscripten's GLUT
