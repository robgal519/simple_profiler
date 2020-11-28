cmake_minimum_required (VERSION 2.8.11)
project (profiler_lib)

add_library(profiler ${CMAKE_CURRENT_SOURCE_DIR}/src/profiler.c ${CMAKE_CURRENT_SOURCE_DIR}/src/profiler_interface_provider.c)
target_include_directories (profiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable (profilerDemo main.c)
target_compile_options(profilerDemo PRIVATE -finstrument-functions)
target_link_libraries (profilerDemo LINK_PRIVATE profiler)