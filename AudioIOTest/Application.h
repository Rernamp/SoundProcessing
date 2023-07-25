#pragma once

#include <BaseSoundProcessingApplication.h>

namespace UDA {
    class Application : BaseSoundProcessingApplication {
    public:
        Application(std::string pathToInputFile, std::string pathToOutputFile) : BaseSoundProcessingApplication(pathToInputFile, pathToOutputFile) {

        }

        void run() {
            
        }
    private:

    };
}