#include "goopylib/goopylib.h"

int main() {
    gp::init();

    auto window = gp::Window(812, 812, "Batch Rendering Lines!");

    int N = 100;
    float distance = 812.0f / (float) N;

    std::vector<gp::Line> lines;

    for (int i = 0; i < N; i++) {
        float pos = distance * (float) i - 406;

        lines.push_back({{pos, -406.0f},
                         {pos, 406.0f}, 3.0f});

        lines.push_back({{-406.0f, pos},
                         {406.0f,  pos}, 3.0f});
    }

    for (auto line: lines) {
        line.draw(window);
    }

    while (window.isOpen()) {
        gp::update();
    }

    gp::terminate();
    return 0;
}
