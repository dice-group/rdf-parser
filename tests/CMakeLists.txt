cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



# add the exectutable for all tests
add_executable(tests Tests.cpp)

target_link_libraries(tests
        rdf-parser
        ${CONAN_LIBS}
        )

set_property(TARGET tests PROPERTY CXX_STANDARD 20)


# copy files for testing to the binary folder
file(COPY datasets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#download some files for the file parsers
download_file(https://upload.wikimedia.org/wikipedia/commons/9/91/Octicons-mark-github.svg)
file(ARCHIVE_EXTRACT INPUT in_file.zip)



function(download_file url filename  )

    if(NOT EXISTS ${filename})
        file(DOWNLOAD ${url} ${filename}
                TIMEOUT 60  # seconds
                )
    endif()
endfunction(download_file)

