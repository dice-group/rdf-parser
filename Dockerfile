FROM ubuntu:focal AS builder
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get -qq update && \
    apt-get -qq install -y cmake git python3-pip python3-setuptools python3-wheel g++



# make build dir
RUN mkdir /rdf-parser
RUN mkdir /rdf-parser/build


# setup conan
RUN pip3 install conan
RUN conan user && \
    conan profile new --detect default && \
    conan profile update settings.compiler.libcxx=libstdc++11 default && \
    conan profile update settings.compiler.version=9 default && \
    conan remote add dice-group https://api.bintray.com/conan/dice-group/tentris


# copy conan and run conan
COPY conanfile.py /rdf-parser/conanfile.py
RUN cd rdf-parser/build && \
    conan install .. --build=missing

 # copy project files except for conanfile (see above)
 COPY include /rdf-parser/include
 COPY cmake /rdf-parser/cmake
 COPY tests /rdf-parser/tests
 COPY CMakeLists.txt /rdf-parser/CMakeLists.txt


# change working directory
WORKDIR /rdf-parser/build

# run cmake
RUN cmake -Drdf_parser_BUILD_TESTS=ON ..
# build
RUN make -j $(nproc)

WORKDIR /rdf-parser/build

RUN pwd

CMD ["./tests/bin/tests"]

RUN pwd
