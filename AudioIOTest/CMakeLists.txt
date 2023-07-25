add_executable(AudioIOTest)

add_library(AudioIOTestCommonAplication INTERFACE)

target_include_directories(AudioIOTestCommonAplication INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(AudioIOTestCommonAplication INTERFACE
    Application.h
    main.cpp
)

add_subdirectory(config)

target_link_libraries(AudioIOTest PRIVATE
    AudioIOTestCommonAplication 
    AudioFile
    LFramework
)
