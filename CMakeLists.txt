 cmake_minimum_required(VERSION 3.15)

project(cmsis_test C CXX)

add_executable(cmsis_test)

set(KFR_ENABLE_DFT 1)
set(KFR_ENABLE_DFT_NP 1)

add_subdirectory(Dependencies/CMSIS-DSP)
add_subdirectory(Dependencies/AudioFile)
add_subdirectory(Dependencies/Math)
add_subdirectory(Dependencies/LFramework)


add_subdirectory(Src)

target_link_libraries(cmsis_test PRIVATE
    CommonAplication 
    CMSISDSP
    AudioFile
    Processing
    LFramework
)


