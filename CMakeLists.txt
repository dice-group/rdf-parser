cmake_minimum_required(VERSION 3.12)
project(rdf-parser VERSION 0.11.0)
set(CMAKE_CXX_STANDARD 20)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# installation directories
set(rdf-parser_INSTALL_INCLUDE_DIR "include" CACHE STRING "The installation include directory")
set(rdf-parser_INSTALL_CMAKE_DIR "share/rdf-parser/cmake" CACHE STRING "The installation cmake directory")


# define a header-only library
add_library(rdf-parser INTERFACE)
add_library(Dice::rdf-parser ALIAS rdf-parser )

target_include_directories(rdf-parser INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${rdf-parser_INSTALL_CMAKE_DIR}>
        )
target_link_libraries(rdf-parser INTERFACE  ${CONAN_LIBS})

# testing
option(RDF_PARSER_BUILD_TESTS "Build rdf-parser tests." OFF)
#if(RDF_PARSER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
#endif()

# require C++20
target_compile_features(rdf-parser INTERFACE cxx_std_20)

# Make package findable
configure_file(cmake/dummy-config.cmake.in rdf-parser-config.cmake @ONLY)

# Enable version checks in find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(rdf-parser-config-version.cmake COMPATIBILITY SameMajorVersion)

# install and export target
install(TARGETS rdf-parser EXPORT rdf-parser-targets)

install(EXPORT rdf-parser-targets
        FILE rdf-parser-config.cmake
        NAMESPACE Dice::
        DESTINATION ${rdf-parser_INSTALL_CMAKE_DIR}
        )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rdf-parser-config-version.cmake DESTINATION ${rdf-parser_INSTALL_CMAKE_DIR})
install(DIRECTORY include/ DESTINATION ${rdf-parser_INSTALL_INCLUDE_DIR})
