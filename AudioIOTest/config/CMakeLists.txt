target_include_directories(AudioIOTestCommonAplication INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(AudioIOTestCommonAplication INTERFACE
    LFrameworkConfig.h
)