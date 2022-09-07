include_directories(${CMAKE_SOURCE_DIR}/string_lib/string_lib)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(TestApp TestApp.cpp)

target_link_libraries(TestApp debug string_lib.lib)
target_link_libraries(TestApp optimized string_lib.lib)