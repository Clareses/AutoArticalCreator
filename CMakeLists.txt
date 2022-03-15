project(AutoArticalCreator)

cmake_minimum_required(VERSION 3.10)

aux_source_directory(./project ProjectDir)
aux_source_directory(./project/src SrcDir)

add_executable(example ${ProjectDir} ${SrcDir})

include_directories(./project/include)