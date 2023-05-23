
#include <iostream>

#include <Application.h>

int main(int argc, char* argv[]) {
    using namespace UDA;

    if (argc != 4) {
        std::cout << "Infalid number input parameter" << std::endl;
        return -1;
    }

    std::cout << "Start application" << std::endl;

    Application app {argv[1], argv[2], argv[3]};

    app.run();
}