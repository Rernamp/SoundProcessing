 cmake_minimum_required(VERSION 3.15)

project(cmsis_test C CXX)

add_executable(cmsis_test)

set(KFR_ENABLE_DFT 1)

add_subdirectory(Dependencies/CMSIS-DSP)
add_subdirectory(Dependencies/AudioFile)
add_subdirectory(Dependencies/kfr)

add_subdirectory(Src)

target_link_libraries(cmsis_test PRIVATE
    CommonAplication
    CMSISDSP
    AudioFile
    kfr
    kfr_dft
    use_arch
)


