 cmake_minimum_required(VERSION 3.15)

project(SoundProcessing C CXX)

set(KFR_ENABLE_DFT 1)
set(KFR_ENABLE_DFT_NP 1)

add_subdirectory(Dependencies/CMSIS-DSP)
add_subdirectory(Dependencies/AudioFile)
add_subdirectory(Dependencies/Math)
add_subdirectory(Dependencies/LFramework)


add_subdirectory(CMSIS-LC-NLMS)
add_subdirectory(AudioIOTest)

