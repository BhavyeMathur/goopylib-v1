#include "goopylib/goopylib.h"
#include <iostream>
#include <filesystem>

#define SET_TRANSPARENCY(x, y, val) if ((x) < xN and (x) >= 0 and (y) < yN and (y) >= 0) { images[xN * (x) + (y)].setTransparency(val); }
#define SET_TRANSPARENCY4(x, y, v1, v2, v3, v4) if ((x) < xN and (x) >= 0 and (y) < yN and (y) >= 0) { images[xN * (x) + (y)].setTransparency(v1, v2, v3, v4); }


int main() {
    gp::init();

    auto window = gp::Window(812, 812, "Batch Rendering Images!");
    window.setBackground(gp::Color(20, 20, 20));

    auto controller = gp::CameraController(window);

    int xN = 24;
    int yN = 24;

    float width = 812.0f / (float) xN;
    float height = 812.0f / (float) yN;

    std::vector<gp::Image> images;

    std::filesystem::path cwd = std::filesystem::current_path();
    std::string path = cwd.c_str();

    std::string paths[] = {path + "/assets/cobblestone.png",
                           path + "/assets/andesite.png",
                           path + "/assets/cracked_stone_bricks.png",
                           path + "/assets/stone.png",
                           path + "/assets/gravel.png",
                           path + "/assets/grass_block_top.png",
                           path + "/assets/coal_ore.png",
                           path + "/assets/iron_ore.png",
                           path + "/assets/copper_ore.png",
                           path + "/assets/diamond_ore.png",
                           path + "/assets/gold_ore.png",
                           path + "/assets/dead_tube_coral_block.png",
                           path + "/assets/dead_horn_coral_block.png",
                           path + "/assets/dead_bubble_coral_block.png",
                           path + "/assets/dead_brain_coral_block.png",
                           path + "/assets/stone_bricks.png",
                           path + "/assets/light_gray_concrete_powder.png"};

    for (int i = 0; i < xN; i++) {
        float x = width * (float) i + width / 2 - 406;

        for (int j = 0; j < yN; j++) {
            float y = height * (float) j + height / 2 - 406;

            images.push_back({paths[rand() % 17].c_str(), {x, y}, width, height});
            images.back().setAnchor(0, 0);
            images.back().draw(&window);
        }
    }

    while (window.isOpen()) {
        gp::update();

        for (auto &object: images) {
            object.setTransparency(0.1);
        }

        auto pos = window.getMousePosition();
        pos = window.toWorld(pos);
        int x = (int) ((pos.x + 406) / width);
        int y = (int) ((pos.y + 406) / height);

        SET_TRANSPARENCY(x, y, 1)

        SET_TRANSPARENCY4(x - 1, y, 0.5, 1, 1, 0.5)
        SET_TRANSPARENCY4(x + 1, y, 1, 0.5, 0.5, 1)
        SET_TRANSPARENCY4(x, y - 1, 0.5, 0.5, 1, 1)
        SET_TRANSPARENCY4(x, y + 1, 1, 1, 0.5, 0.5)

        SET_TRANSPARENCY4(x - 1, y - 1, 0.3, 0.5, 1, 0.5)
        SET_TRANSPARENCY4(x - 1, y + 1, 0.5, 1, 0.5, 0.3)
        SET_TRANSPARENCY4(x + 1, y - 1, 0.5, 0.3, 0.5, 1)
        SET_TRANSPARENCY4(x + 1, y + 1, 1, 0.5, 0.3, 0.5)

        SET_TRANSPARENCY4(x - 2, y, 0.1, 0.5, 0.5, 0.1)
        SET_TRANSPARENCY4(x + 2, y, 0.5, 0.1, 0.1, 0.5)
        SET_TRANSPARENCY4(x, y - 2, 0.1, 0.1, 0.5, 0.5)
        SET_TRANSPARENCY4(x, y + 2, 0.5, 0.5, 0.1, 0.1)

        SET_TRANSPARENCY4(x - 2, y + 1, 0.1, 0.5, 0.3, 0.1)
        SET_TRANSPARENCY4(x - 2, y - 1, 0.1, 0.3, 0.5, 0.1)
        SET_TRANSPARENCY4(x + 2, y + 1, 0.5, 0.1, 0.1, 0.3)
        SET_TRANSPARENCY4(x + 2, y - 1, 0.3, 0.1, 0.1, 0.5)

        SET_TRANSPARENCY4(x - 1, y - 2, 0.1, 0.1, 0.5, 0.3)
        SET_TRANSPARENCY4(x + 1, y - 2, 0.1, 0.1, 0.3, 0.5)
        SET_TRANSPARENCY4(x - 1, y + 2, 0.3, 0.5, 0.1, 0.1)
        SET_TRANSPARENCY4(x + 1, y + 2, 0.5, 0.3, 0.1, 0.1)

        SET_TRANSPARENCY4(x - 2, y - 2, 0.1, 0.1, 0.2, 0.1)
        SET_TRANSPARENCY4(x + 2, y - 2, 0.1, 0.1, 0.1, 0.3)
        SET_TRANSPARENCY4(x - 2, y + 2, 0.1, 0.3, 0.1, 0.1)
        SET_TRANSPARENCY4(x + 2, y + 2, 0.2, 0.1, 0.1, 0.1)

        controller.update();
    }

    gp::terminate();
    return 0;
}
