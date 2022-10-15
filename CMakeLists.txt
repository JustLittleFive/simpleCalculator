cmake_minimum_required(VERSION 3.16)

project(simpleCalculator)

aux_source_directory(./src DIR_SRC)

include_directories(inc)

add_executable(simpleCalculator ${DIR_SRC})

SET(EXECUTABLE_OUTPUT_PATH ./bin)

SET(LIBRARY_OUTPUT_PATH ./build)