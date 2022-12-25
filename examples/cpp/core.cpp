#include "goopylib/goopylib.h"
#include <iostream>

int main() {
    gp::init();

    std::cout << "Refresh Rate: " << gp::getRefreshRate() << std::endl;
    std::cout << "Screen Width: " << gp::getScreenWidth() << std::endl;
    std::cout << "Screen Height: " << gp::getScreenHeight() << std::endl;
    std::cout << "# of Monitors: " << gp::getNumberOfMonitors() << std::endl;
    std::cout << std::endl;

    std::cout << "GLFW Compiled Version: " << gp::glfwCompiledVersion() << std::endl;
    std::cout << "GLFW Current Version: " << gp::glfwCurrentVersion() << std::endl;

    // goopylib provides 3 update functions
    gp::update();

    // These have been commented out because without an active window, they will simply pause the program
    // gp::updateOnEvent();
    // gp::updateTimeout(60);

    // edit the default update rate to update at 30 FPS
    gp::setBufferSwapInterval(30);

    gp::terminate();
}
