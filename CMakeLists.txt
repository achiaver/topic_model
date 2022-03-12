cmake_minimum_required(VERSION 3.22)

project(topic_model VERSION 0.0.1 LANGUAGES C)

configure_file(main.h.in main.h)


add_subdirectory(libs)
add_executable(${CMAKE_PROJECT_NAME} main.c)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC libs)

target_include_directories(${CMAKE_PROJECT_NAME}
                        PUBLIC
                        "${PROJECT_BINARY_DIR}")
