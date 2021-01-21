FROM ubuntu:focal AS builder
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -qq update
RUN apt-get -qq install -y make cmake git libstdc++-10-dev g++-10
RUN apt-get -qq install -y python3-pip python3-setuptools python3-wheel
# uuid-dev pkg-config openjdk-11-jdk

# setup conan
RUN pip3 install conan
RUN conan user && \
    conan profile new --detect default && \
    conan profile update settings.compiler=gcc default &&\
    conan profile update settings.compiler.libcxx=libstdc++11  default  && \
    conan profile update settings.compiler.version=10 default

RUN conan remote add dice "https://api.bintray.com/conan/dice-group/tentris"

WORKDIR /rdf-parser
COPY CMakeLists.txt CMakeLists.txt
COPY tests tests
COPY include include
COPY cmake cmake
COPY conanfile.py conanfile.py

RUN conan profile update env.CXX=/usr/bin/g++-10 default && \
    conan profile update env.CC=/usr/bin/g-10 default

WORKDIR /rdf-parser/build
RUN conan install .. --build=missing  -o rdf-parser:with_tests=True
#RUN conan install .. --build=missing --profile clang11 -o rdf-parser:with_tests=True

#RUN conan create . "rdf-parser/test1@dice-group/stable" --build missing --profile gcc10
#RUN conan create . "rdf-parser/test2dice-group/stable" --build missing --profile gcc10 -o rdf-parser:with_tests=True

## change working directory
WORKDIR /rdf-parser/build
#
# run cmake
RUN CC=gcc-10 CXX=g++-10 cmake -DCMAKE_BUILD_TYPE=Release -DRDF_PARSER_BUILD_TESTS=ON ..
# build
RUN make -j $(nproc)

WORKDIR /rdf-parser/build
RUN ./bin/tests

