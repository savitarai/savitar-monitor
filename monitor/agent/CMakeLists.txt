aux_source_directory(. SRC_FILES)
add_executable(mon_agent ${SRC_FILES})
target_link_libraries(mon_agent util log4cpp pthread)
