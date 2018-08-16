cmake_minimum_required(VERSION 3.10)
project(MorphoTooth)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})

include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)
