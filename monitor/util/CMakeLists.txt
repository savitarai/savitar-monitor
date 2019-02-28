cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_FILES)


add_library(util SHARED ${SRC_FILES})

add_library(util_static STATIC ${SRC_FILES})
set_target_properties(util_static PROPERTIES OUTPUT_NAME util)
set_target_properties(util PROPERTIES VERSION 1 )
target_link_libraries(util log4cpp pthread)
#set(CMAKE_INSTALL_PREFIX ${smon_SOURCE_DIR})

#install(TARGETS util DESTINATION lib)
#install(FILES shm.h util_str.h DESTINATION include/util)
