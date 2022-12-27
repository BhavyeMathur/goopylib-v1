#include "goopylib/goopylib.h"
#include <iostream>

void ResizeCallback(gp::Window *window, int width, int height) {
    std::cout << gp::strformat("Resized window to size (%i, %i)", width, height) << std::endl;
}

void CloseCallback(gp::Window *window) {
    std::cout << "Closed window" << std::endl;
}

void DestroyCallback(gp::Window *window) {
    std::cout << "Destroyed window" << std::endl;
}

void MaximizeCallback(gp::Window *window, bool maximized) {
    std::cout << gp::strformat("Window maximized? %d", maximized) << std::endl;
}

void MinimizeCallback(gp::Window *window, bool minimized) {
    std::cout << gp::strformat("Window minimized? %d", minimized) << std::endl;
}

void FocusedCallback(gp::Window *window, bool focused) {
    std::cout << gp::strformat("Window focused? %d", focused) << std::endl;
}

void SpaceKeyCallback(gp::Window *window, int action) {
    std::cout << gp::strformat("Space key pressed? %d", action) << std::endl;
}

void MouseMotionCallback(gp::Window *window, float xPos, float yPos) {
    // Silenced because it clutters the console
    // std::cout << gp::strformat("Cursor moved to (%f, %f)", xPos, yPos) << std::endl;
}

void MouseEnterCallback(gp::Window *window, bool entered) {
    std::cout << gp::strformat("Mouse entered window? %d", entered) << std::endl;
}

void ScrollCallback(gp::Window *window, float xScroll, float yScroll) {
    std::cout << gp::strformat("Scroll changed to (%f, %f)", xScroll, yScroll) << std::endl;
}

void LeftClickCallback(gp::Window *window, bool pressed) {
    std::cout << gp::strformat("Left button clicked? %d", pressed) << std::endl;
}

void MiddleClickCallback(gp::Window *window, bool pressed) {
    std::cout << gp::strformat("Middle button clicked? %d", pressed) << std::endl;
}

void RightClickCallback(gp::Window *window, bool pressed) {
    std::cout << gp::strformat("Right button clicked? %d", pressed) << std::endl;
}

int main() {
    gp::init();

    auto window = gp::Window(500, 500, "Window Callback Functions");

    window.setResizable(true);
    window.setSizeLimits(200, 200, 900, 900);

    window.setResizeCallback(ResizeCallback);
    window.setCloseCallback(CloseCallback);
    window.setDestroyCallback(DestroyCallback);

    window.setMaximizeCallback(MaximizeCallback);
    window.setMinimizeCallback(MinimizeCallback);
    window.setFocusCallback(FocusedCallback);

    window.setKeyCallback(GP_KEY_SPACE, SpaceKeyCallback);

    window.setMouseMotionCallback(MouseMotionCallback);
    window.setMouseEnterCallback(MouseEnterCallback);
    window.setScrollCallback(ScrollCallback);

    window.setLeftClickCallback(LeftClickCallback);
    window.setMiddleClickCallback(MiddleClickCallback);
    window.setRightClickCallback(RightClickCallback);

    while (window.isOpen()) {
        gp::update();
    }

    gp::terminate();

    return 0;
}
