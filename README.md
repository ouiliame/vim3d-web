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

**NOTE:** the original build system relied on [this Makefile](https://github.com/pyramation/vim3d/blob/5486287138bcfb3def4ff608ca898b6228db6397/src/Makefile); we updated it to use CMake.

```bash
mkdir build
cd build
emcmake cmake ..
emmake make
```

To clean up build artifacts, simply remove the `build/` directory.

```bash
rm -rf build
```

