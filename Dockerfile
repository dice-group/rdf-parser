FROM ubuntu:focal AS builder
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -qq update
RUN apt-get -qq install -y make cmake git libstdc++-10-dev g++-10 clang-11
RUN apt-get -qq install -y python3-pip python3-setuptools python3-wheel
# uuid-dev pkg-config openjdk-11-jdk

# setup conan
RUN pip3 install conan
RUN conan user && \
    conan profile new --detect default && \
    conan profile update settings.compiler.libcxx=libstdc++11  default  && \
    conan profile update settings.compiler.version=10 default  && \
    conan profile new --detect clang11 && \
    conan profile update settings.compiler=clang clang11 &&\
    conan profile update settings.compiler.version=11 clang11 && \
    conan profile update settings.compiler.libcxx=libstdc++11 clang11

RUN conan remote add dice "https://api.bintray.com/conan/dice-group/tentris"

WORKDIR /rdf-parser
COPY CMakeLists.txt CMakeLists.txt
COPY tests tests
COPY include include
COPY cmake cmake
COPY conanfile.py conanfile.py

#gcc

WORKDIR /rdf-parser/build_gcc

ENV CXX="g++-10"
ENV CC="gcc10"

RUN conan install .. --build=missing  -o rdf-parser:with_tests=True

## change working directory
WORKDIR /rdf-parser/build_gcc

#
# run cmake
RUN CC=gcc-10 CXX=g++-10 cmake -DCMAKE_BUILD_TYPE=Release -DRDF_PARSER_BUILD_TESTS=ON ..
# build
RUN make -j $(nproc)

#for clang
## change working directory
WORKDIR /rdf-parser/build_clang

ENV CXX="clang++-11"
ENV CC="clang-11"

RUN conan install .. --build=missing --profile clang11 -o rdf-parser:with_tests=True
# run cmake
RUN CC=clang-11 CXX=clang++-11 cmake -DCMAKE_BUILD_TYPE=Release -DRDF_PARSER_BUILD_TESTS=ON ..
# build
RUN make -j $(nproc)

WORKDIR /rdf-parser/build_clang
RUN ./bin/tests

WORKDIR /rdf-parser/build_gcc
RUN ./bin/tests

WORKDIR /rdf-parser/

#RUN conan create . "rdf-parser/test1@dice-group/stable" --build missing
#RUN conan create . "rdf-parser/test2dice-group/stable" --build missing --profile clang11