add_library(libs 
    parameters.c
    parameters.h
    rsm.c
    rsm.h
    random_lib.c
    random_lib.h
    pcg_basic.c
    pcg_basic.h
    dataset.c
    dataset.h)

target_include_directories(libs PUBLIC .)
