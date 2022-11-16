FROM emscripten/emsdk:latest

RUN DEBIAN_FRONTEND="noninteractive" apt-get update \
    && apt-get install -y ninja-build rsync ssh \
    && apt-get clean

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
) > /etc/ssh/sshd_config_test_clion \
    && mkdir /run/sshd

# We need at least CMake 3.21 to support CMAKE_TOOLCHAIN_FILE from environment
RUN wget --no-verbose https://github.com/Kitware/CMake/releases/download/v3.22.5/cmake-3.22.5-linux-x86_64.tar.gz --directory-prefix=/tmp \
    && tar xf /tmp/cmake-3.22.5-linux-x86_64.tar.gz -C /opt --strip-components=1 \
    && rm /tmp/cmake-3.22.5-linux-x86_64.tar.gz \
    && echo 'PATH=/opt/bin:$PATH' >> /etc/bash.bashrc

RUN mkdir /clion && ( \
        echo 'export CMAKE_TOOLCHAIN_FILE=/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake'; \
        echo 'export CMAKE_GENERATOR=Ninja'; \
        echo 'export CMAKE_C_COMPILER=$(which emcc)'; \
        echo 'export CMAKE_CXX_COMPILER=$(which em++)'; \
        echo 'export CC=$(which emcc)'; \
        echo 'export CXX=$(which em++)'; \
    ) > /clion/emsdk.sh \
    && chmod a+x /clion/emsdk.sh

RUN useradd -m user \
    && yes password | passwd user

RUN usermod -s /bin/bash user

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]