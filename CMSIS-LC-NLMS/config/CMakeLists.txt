target_include_directories(CommonAplication INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(CommonAplication INTERFACE
    LFrameworkConfig.h
)