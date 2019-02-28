aux_source_directory(. SRC_FILES)

link_libraries(monapi)

foreach(src ${SRC_FILES})
    string(REPLACE ".cpp" "" bin ${src})
    string(REPLACE "./" "" bin ${bin})
    add_executable(${bin} ${src})
endforeach()

