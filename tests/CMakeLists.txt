include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.1
        GIT_SHALLOW TRUE
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest ALIAS gtest)
add_library(GTest::Main ALIAS gtest_main)

include(GoogleTest)
# add the executable for all tests
add_executable(tests Tests.cpp)

target_link_libraries(tests
        GTest::GTest
        GTest::Main
        rdf-parser
        )

set_property(TARGET tests PROPERTY CXX_STANDARD 20)

gtest_discover_tests(tests)


# copy files for testing to the binary folder
file(COPY datasets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#download some files for the file parsers

function(download_file url filename)
    if (NOT EXISTS ${filename})
        file(DOWNLOAD ${url} ${filename}
                TIMEOUT 60  # seconds
                )
    endif ()
endfunction(download_file)

download_file(https://hobbitdata.informatik.uni-leipzig.de/ISWC2020_Tentris/swdf.zip
        ${CMAKE_BINARY_DIR}/tests/swdf.zip)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/tests/swdf.nt)
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xf ${CMAKE_BINARY_DIR}/tests/swdf.zip
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/datasets/
    )
endif ()




