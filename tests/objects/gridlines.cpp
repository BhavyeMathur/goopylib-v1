#include "goopylib.h"

using std::shared_ptr, std::make_shared;

int main() {
    gp::init();

    auto window = gp::Window(812, 812, "Batch Rendering Lines!");

    int N = 100;
    float distance = 812.0f / (float) N;

    std::vector<shared_ptr<gp::Line>> lines;

    for (int i = 0; i < N; i++) {
        float pos = distance * (float) i - 406;

        lines.push_back(std::make_shared<gp::Line>(Point{pos, -406.0f},
                                                   Point{pos, 406.0f}, 3.0f));

        lines.push_back(std::make_shared<gp::Line>(Point{-406.0f, pos},
                                                   Point{406.0f, pos}, 3.0f));
    }

    for (auto line: lines) {
        window.draw(line);
    }

    while (window.isOpen()) {
        gp::update();
    }

    gp::terminate();
    return 0;
}
