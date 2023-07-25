add_executable(CMSIS-LC-NLMS)

add_library(CommonAplication INTERFACE)

target_include_directories(CommonAplication INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(CommonAplication INTERFACE
    Application.h
    main.cpp
)

add_subdirectory(Filters)
add_subdirectory(config)


target_link_libraries(CMSIS-LC-NLMS PRIVATE
    CommonAplication 
    CMSISDSP
    AudioFile
    Processing
    LFramework
)
