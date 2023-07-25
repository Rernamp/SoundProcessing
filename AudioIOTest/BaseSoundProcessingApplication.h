#pragma once

#include <string.h>

#include <AudioFile.h>

namespace UDA {
    class BaseSoundProcessingApplication {
        using AudioFileType = AudioFile<float>;
    public:
        BaseSoundProcessingApplication(std::string pathToInputFile, std::string pathToOutputFile) : _pathToOutputFile(pathToOutputFile) {
            _inputAudioWav.load(pathToInputFile);
        }
    private:
        AudioFileType _inputAudioWav {};
        std::string _pathToOutputFile;
    };
}