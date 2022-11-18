.PHONY: build clean

build:
		mkdir -p build
		EMCC_DEBUG=1 cd build && emcmake cmake .. && emmake make -j 8

run: build
		emrun --browser chrome_canary build/vim3d.html

clean:
		@rm -rf	build