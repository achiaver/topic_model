add_library(libs 
    utils.c
    utils.h
    parameters.c
    parameters.h
    rsm.c
    rsm.h
    ran3.c
    ran3.h)

target_include_directories(libs PUBLIC .)
