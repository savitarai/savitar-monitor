aux_source_directory(. SRC_FILES)

foreach(src ${SRC_FILES})
    string(REPLACE ".cpp" "" bin ${src})
    string(REPLACE "./" "" bin ${bin})
    add_executable(${bin} ${src})
endforeach()

