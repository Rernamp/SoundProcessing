add_library(CommonAplication INTERFACE)

target_include_directories(CommonAplication INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(CommonAplication INTERFACE
    Application.h
    main.cpp
)