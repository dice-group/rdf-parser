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

function(download_file url filename  )

    if(NOT EXISTS ${filename})
        file(DOWNLOAD ${url} ${filename}
                TIMEOUT 60  # seconds
                )
    endif()
endfunction(download_file)

download_file( https://hobbitdata.informatik.uni-leipzig.de/ISWC2020_Tentris/swdf.zip tests/swdf.zip)

execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xkf ${CMAKE_BINARY_DIR}/tests/swdf.zip
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/datasets/
)




