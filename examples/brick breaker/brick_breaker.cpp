#include "goopylib/goopylib.h"


class Brick : public gp::Rectangle {
public:
    Brick(int i, int j)
            : gp::Rectangle({i * s_Width - 450 + s_Width / 2,
                             j * s_Height + 85}, s_Width, s_Height) {

        setColor(gp::Color(255 - j * 20, 255 - j * 20, 255 - j * 20));
    }

    void hit() {
        m_Hits += 1;
        setTransparency(1 - 0.25f * m_Hits);

        if (m_Hits == 4) {
            destroy();
        }
    }

    int m_Hits = 0;

    static const int s_Width = 100;
    static const int s_Height = 55;
};

class Ball : public gp::Circle {
public:
    Ball() : gp::Circle({-250, 20}, 7) {
        setColor(gp::Color(255, 150, 150));
    }

    void update(float dt) {
        if (m_Position.x < -450) {
            setX(-450);
            m_xVel *= -1;
        }
        else if (m_Position.x > 450) {
            setX(450);
            m_xVel *= -1;
        }

        if (m_Position.y > 300) {
            setY(300);
            collide();
        }

        if (abs(m_yVel) < 5) {
            m_yVel -= 0.07;
            m_xVel += 0.07;
        }

        move(70 * m_xVel * dt, 70 * m_yVel * dt);
    }

    void collide() {
        m_yVel *= -1;
    }

    float m_xVel = 0;
    float m_yVel = 0;
};

class Controller : public gp::Rectangle {
public:
    Controller() : gp::Rectangle({0, -220}, 120, 15) {
        setColor(gp::Color(255, 255, 255));
    }

    void update() {
        auto pos = m_Window->toWorld(m_Window->getMousePosition());

        float tmp = m_Position.x;
        setX(max(-m_MaxX, min(m_MaxX, pos.x)));
        m_xVel = m_Position.x - tmp;
    }

    float m_xVel = 0;
    float m_MaxX = 450;
};


int main(int argc, char* argv[]) {
    gp::init();

    auto window = gp::Window(900, 600, "Brick Breaker using goopylib!");
    window.setBackground(gp::Color(25, 25, 25));
    window.setResizable(true);

    window.setMinSize(600, 400);
    window.setAspectRatio(900, 600);

    auto &camera = window.getCamera();

    std::string argv_str(argv[0]);
    std::string base = argv_str.substr(0, argv_str.find_last_of("/"));

    std::string path = base + "/vignette.png";

    auto vignette = gp::Image(path.c_str(), {0, 0}, 900, 600);
    vignette.draw(&window);
    vignette.setTransparency(0.3, 0.3, 0.8, 0.8);

    while (window.isOpen()) {
        camera.setRotation(0);
        camera.setZoom(1);

        auto controller = Controller();
        controller.draw(&window);

        auto ball = Ball();
        ball.draw(&window);

        float transparency = 0;

        std::vector<Brick> bricks;

        for (int i = 0; i < 900 / Brick::s_Width; i++) {
            for (int j = 0; j < 4; j++) {
                bricks.push_back(Brick(i, j));
                bricks.back().draw(&window);
            }
        }

        while (window.isOpen() and !window.checkLeftClick()) {
            if (transparency < 1) {
                transparency += 0.02;
                ball.setTransparency(min(1.0f, transparency));
            }

            controller.update();
            gp::update();
        }

        ball.setTransparency(1);

        float dt = 0;
        float lasthit = 0;

        while (window.isOpen()) {
            float start = gp::getTime();

            if (ball.getY() < -300 or bricks.size() == 0) {
                break;
            }

            if (controller.contains(ball.getPosition())) {
                ball.collide();
                ball.m_xVel = max(-12.0f, min(12.0f, ball.m_xVel * 0.85f + controller.m_xVel * 0.2f));
                ball.move(0, 12);
            }

            for (auto &brick: bricks) {
                if (brick.isDrawn() and brick.contains(ball.getPosition())) {
                    ball.collide();
                    brick.hit();
                    lasthit = gp::getTime();
                    break;
                }
            }

            if (gp::getTime() - lasthit < 0.2) {
                camera.setX(rand() % 8 - 4);
            }
            else {
                camera.setX(0);
            }

            controller.update();
            ball.update(dt);
            gp::update();

            dt = gp::getTime() - start;
        }

        ball.destroy();
        auto start = gp::getTime();
        auto ease = gp::easeBounceOut(4, 0.8);
        float easet = 0.7;

        controller.m_MaxX = 350;

        while (window.isOpen() and gp::getTime() - start < easet) {
            float val = ease(gp::getTime() - start);
            camera.setRotation(4 * val);
            camera.setZoom(1 - 0.02 * val);

            controller.update();
            gp::update();
        }

        while (window.isOpen() and !window.checkLeftClick()) {
            controller.update();
            gp::update();
        }

        while (window.isOpen() and window.checkLeftClick()) {
            controller.update();
            gp::update();
        }

        while (window.isOpen() and camera.getRotation() > 0) {
            camera.rotate(-0.2);
            camera.setZoom(1 - 0.005 * camera.getRotation());

            controller.update();
            gp::update();
        }

        controller.destroy();

        for (auto &brick: bricks) {
            brick.destroy();
        }
    }

    gp::terminate();
    return 0;
}
