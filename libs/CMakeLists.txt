add_library(libs 
    utils.c
    utils.h
    parameters.c
    parameters.h
    rsm.c
    rsm.h)

target_include_directories(libs PUBLIC .)
