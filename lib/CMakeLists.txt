include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} source)

add_library(rbm ${source})
set_target_properties(rbm PROPERTIES OUTPUT_NAME "main")

target_include_directories(rbm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})