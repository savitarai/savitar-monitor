cmake_minimum_required(VERSION 2.8)
project(curltest CXX)

link_libraries(curl)

aux_source_directory(. SRCS)

foreach(src ${SRCS})
    string(REPLACE ".cpp" "" BIN ${src})
    message(${BIN})
    add_executable(${BIN} ${src})
endforeach()
