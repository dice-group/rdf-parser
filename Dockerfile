FROM ubuntu:focal AS builder
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -qq update
RUN apt-get -qq install -y make cmake git libstdc++-10-dev g++10 clang-11
RUN apt-get -qq install -y python3-pip python3-setuptools python3-wheel
# uuid-dev pkg-config openjdk-11-jdk

# setup conan
RUN pip3 install conan
RUN conan user && \
    conan profile new --detect gcc10 && \
    conan profile update settings.compiler.libcxx=libstdc++11  gcc10  && \
    conan profile new --detect clang11 && \
    conan profile update settings.compiler=clang clang11 &&\
    conan profile update settings.compiler.version=11 clang11 && \
    conan profile update settings.compiler.libcxx=libstdc++11 clang11 && \
    conan profile update env.CXX=/usr/bin/clang++-11 clang11 && \
    conan profile update env.CC=/usr/bin/clang-11 clang11

WORKDIR /rdf-parser
COPY conanfile.py conanfile.py

WORKDIR /rdf-parser/conan-cache
RUN conan install .. --build=missing --profile gcc10 -o rdf-parser:with_tests=True
RUN conan install .. --build=missing --profile clang11 -o rdf-parser:with_tests=True

WORKDIR /rdf-parser
COPY CMakeLists.txt CMakeLists.txt
COPY tests tests
COPY include include
COPY cmake cmake

RUN conan create . "rdf-parser/test1@dice-group/stable" --build missing --profile gcc10
RUN conan create . "rdf-parser/test2dice-group/stable" --build missing --profile gcc10 -o rdf-parser:with_tests=True

## change working directory
#WORKDIR /rdf-parser/build
#
## run cmake
#RUN cmake -Drdf_parser_BUILD_TESTS=ON ..
## build
#RUN make -j $(nproc)
#
#WORKDIR /rdf-parser/build
#
#RUN pwd

#CMD ["./tests/bin/tests"]
