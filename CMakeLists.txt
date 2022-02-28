cmake_minimum_required(VERSION 3.22)
project(topic_model VERSION 0.0.1)

add_library(
    rsm
    utils.c
    parameters.c
    rsm.c
)

add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE rsm)
