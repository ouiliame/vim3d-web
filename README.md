# vim3d

## Build

```bash
mkdir build
cd build
emcmake cmake ..
emmake make
```

## Using Docker

### Build Docker image

```bash
docker build -f Dockerfile -t clion/emscripten .
```

### Run

```bash
docker run -d --cap-add sys_ptrace -p127.0.0.1:2222:22 --name clion_emscripten clion/emscripten
```