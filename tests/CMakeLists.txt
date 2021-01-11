cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



# add the exectutable for all tests
add_executable(tests Tests.cpp)

target_link_libraries(tests
        rdf-parser
        ${CONAN_LIBS}
        )

set_property(TARGET tests PROPERTY CXX_STANDARD 17)


# copy files for testing to the binary folder
file(COPY datasets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
