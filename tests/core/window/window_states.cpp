#include "goopylib/goopylib.h"

int main() {
    gp::init();

    // Create a new window of size 500x500 pixels, then update it to show the window
    auto window = gp::Window(500, 500, "Window States");
    gp::update();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // After 1 second, minimize the window
    window.minimize();
    gp::update();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // After 1 second, restore the window to normal
    window.restore();
    gp::update();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // After 1 second, maximize the window
    window.maximize();
    gp::update();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // After 1 second, restore the window to normal
    window.restore();
    gp::update();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    gp::terminate();
}
