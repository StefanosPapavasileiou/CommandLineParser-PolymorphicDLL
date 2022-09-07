link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
file(GLOB headers *.h)
file(GLOB src *.cpp)

#add_library(string_lib SHARED ${CMAKE_SOURCE_DIR}/string_lib/string_lib/string_lib.cpp ${CMAKE_SOURCE_DIR}/string_lib/string_lib/string_lib.h)
add_library(string_lib SHARED ${headers} ${src})

add_compile_definitions(-Dstring_lib_EXPORT)



