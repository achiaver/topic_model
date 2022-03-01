cmake_minimum_required(VERSION 3.22)

project(topic_model VERSION 0.0.1)

configure_file(main.h.in main.h)
add_executable(${CMAKE_PROJECT_NAME} main.c)

target_include_directories(${CAMKE_PROJECT_NAME}
                        PUBLIC
                        "${PROJECT_BINARY_DIR}")