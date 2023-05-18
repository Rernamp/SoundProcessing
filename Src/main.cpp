
#include <iostream>

#include <Application.h>

int main(int argc, char* argv[]) {
    using namespace UDA;

    if (argc != 4) {
        return -1;
    }

    Application app {argv[1], argv[2], argv[3]};

    app.run();
}