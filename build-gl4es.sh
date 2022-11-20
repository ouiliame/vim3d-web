cd gl4es
rm -rf build
mkdir build; cd build; emcmake cmake .. -DCMAKE_BUILD_TYPE=Debug -DNOX11=ON -DNOEGL=ON -DSTATICLIB=ON; make -j 8
