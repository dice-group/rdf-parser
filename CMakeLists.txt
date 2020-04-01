cmake_minimum_required(VERSION 3.12)
project(rdf_parser VERSION 0.9.0)
set(CMAKE_CXX_STANDARD 17)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# installation directories
set(rdf_parser_INSTALL_INCLUDE_DIR "include" CACHE STRING "The installation include directory")
set(rdf_parser_INSTALL_CMAKE_DIR "share/rdf_parser/cmake" CACHE STRING "The installation cmake directory")


# define a header-only library
add_library(rdf_parser INTERFACE)
add_library(Dice::rdf_parser ALIAS rdf_parser)

target_include_directories(rdf_parser INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${rdf_parser_INSTALL_CMAKE_DIR}>
        )
target_link_libraries(rdf_parser INTERFACE  ${CONAN_LIBS})

# testing
option(rdf_parser_BUILD_TESTS "Build rdf_parser tests." OFF)
#if(rdf_parser_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
#endif()

# require C++17
target_compile_features(rdf_parser INTERFACE cxx_std_17)

# Make package findable
configure_file(cmake/dummy-config.cmake.in rdf_parser-config.cmake @ONLY)

# Enable version checks in find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(rdf_parser-config-version.cmake COMPATIBILITY SameMajorVersion)

# install and export target
install(TARGETS rdf_parser EXPORT rdf_parser-targets)

install(EXPORT rdf_parser-targets
        FILE rdf_parser-config.cmake
        NAMESPACE Dice::
        DESTINATION ${rdf_parser_INSTALL_CMAKE_DIR}
        )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/rdf_parser-config-version.cmake DESTINATION ${rdf_parser_INSTALL_CMAKE_DIR})
install(DIRECTORY include/ DESTINATION ${rdf_parser_INSTALL_INCLUDE_DIR})
