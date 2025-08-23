FROM ubuntu:25.04
LABEL authors="akrimm"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -q  && apt-get install --no-install-recommends -qy wget gpg ca-certificates software-properties-common \
    bash file locales build-essential sudo cmake git make ninja-build cppzmq-dev libfftw3-dev meson ninja-build \
    clang-18 clang-tools-18 clang-20 clang-tools-20 libc++-20-dev libc++abi-20-dev gdb lldb-20 gcc-14 g++-14 gcc-15 g++-15 \
    ccache mold pkg-config

RUN locale-gen en_US.UTF-8 && echo 'LANG="en_US.UTF-8"'>/etc/default/locale 

RUN dpkg-reconfigure --frontend=noninteractive locales && update-locale LANG=en_US.UTF-8 \
    && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-14 110 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 110 --slave /usr/bin/g++ g++ /usr/bin/g++-14 --slave /usr/bin/gcov gcov /usr/bin/gcov-14


# Clone and build GNURADIO4
WORKDIR /opt
RUN git clone https://github.com/gnuradio/gnuradio4.git
WORKDIR /opt/gnuradio4
RUN mkdir build && cd build && \
    #cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithAssert -DGR_ENABLE_BLOCK_REGISTRY=OFF -DENABLE_TESTING=OFF -DENABLE_EXAMPLES=OFF .. && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithAssert -DGR_ENABLE_BLOCK_REGISTRY=ON -DENABLE_TESTING=OFF -DENABLE_EXAMPLES=OFF .. && \
    ninja -j8 && ninja install

# # This is a complete hack until GR4.0 repo installs to right places
# RUN mkdir /usr/local/include/gnuradio-4.0 \
#     && cp -r /opt/gnuradio4/core/include/gnuradio-4.0 /usr/include/ \
#     && cp -r /opt/gnuradio4/meta/include/gnuradio-4.0 /usr/local/include/ \
#     && cp /opt/gnuradio4/third_party/magic_enum/*.hpp /usr/local/include/ \
#     && cp /opt/gnuradio4/build/core/include/gnuradio-4.0/config.hpp /usr/local/include/gnuradio-4.0/

RUN ls /opt/gnuradio4/build/core/
RUN cp /opt/gnuradio4/build/core/libgnuradio-blocklib-core.so /usr/local/lib/ 

# Install all the headers
RUN find /opt/gnuradio4/blocks -type d -name 'gnuradio-4.0' -exec cp -r {} /usr/local/include/ \;

# RUN rm -rf /opt/gnuradio4/build/

# Add additional dependencies for this OOT module
# RUN apt-get install --no-install-recommends -qy ...

RUN rm -rf /var/lib/apt/lists/*

RUN echo "ubuntu ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/ubuntu
USER ubuntu
WORKDIR /code
ENTRYPOINT ["/bin/bash", "-l", "-c"]


