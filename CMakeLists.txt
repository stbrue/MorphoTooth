cmake_minimum_required(VERSION 3.10)
project(ToothMaker)

set(CMAKE_CXX_STANDARD 14)

add_executable(ToothMaker main.cpp Cell.cpp Cell.h Initial.cpp Initial.h Grid.cpp Grid.h Output.cpp Output.h Geometrics.cpp Geometrics.h Model.cpp Model.h Parameters.cpp Parameters.h)