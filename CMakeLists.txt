cmake_minimum_required(VERSION 3.16)
project(rdf-parser VERSION 0.14.0)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


### conan cmake
if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif ()

include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)

conan_cmake_run(CONANFILE conanfile.py
        GENERATORS cmake_find_package
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)

if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    endif ()
endif ()


# installation directories
set(rdf-parser_INSTALL_INCLUDE_DIR "include" CACHE STRING "The installation include directory")
set(rdf-parser_INSTALL_CMAKE_DIR "share/rdf-parser/cmake" CACHE STRING "The installation cmake directory")


# define a header-only library
add_library(rdf-parser INTERFACE)
add_library(Dice::rdf-parser ALIAS rdf-parser)

find_package(dice-hash REQUIRED)
find_package(robin_hood REQUIRED)
find_package(fmt REQUIRED)
find_package(pegtl REQUIRED)



target_include_directories(rdf-parser INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${rdf-parser_INSTALL_CMAKE_DIR}>
        )
target_link_libraries(rdf-parser INTERFACE
        robin_hood::robin_hood
        dice-hash::dice-hash
        fmt::fmt
        taocpp::pegtl)

# testing
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()

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
