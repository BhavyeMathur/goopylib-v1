import goopylib.imports as gp

import random
import time
import os

PATH = os.path.dirname(os.path.realpath(__file__))


class Brick(gp.Image):
    width = 100
    height = 55

    colors = ["blue", "purple", "yellow", "green"]

    def __init__(self, i, j):
        super().__init__(f"{PATH}/assets/element_{self.colors[j]}_rectangle.png",
                         (i * self.width - 450 + self.width / 2, j * self.height + 85),
                         self.width, self.height)
        self.hits = 0

    def hit(self):
        self.hits += 1
        self.set_transparency(1 - 0.25 * self.hits)


class Ball(gp.Circle):
    def __init__(self, p):
        super().__init__(p, 10)
        self.set_color((255, 255, 255))
        
        self.velx = 0 if p[0] < 0 else -5
        self.vely = -7

        self.lastcontrollerx = 0

    def update(self, dt, controller, blocks):
        if self.x < -450 or self.x > 450:
            self.velx *= -1
        if self.y < -300 or self.y > 300:
            self.vely *= -1

        velx = controller.x - self.lastcontrollerx
        self.lastcontrollerx = controller.x

        if controller.contains(*self.position):
            self.velx = max(-12, min(12, self.velx * 0.85 + velx * 0.2))
            self.vely *= -1
            self.y = controller.y + 12

        for block in blocks:
            if block.contains(*self.position):
                self.vely *= -1
                block.hit()

                if block.hits == 4:
                    block.destroy()
                    blocks.remove(block)

        self.move(70 * self.velx * dt, 70 * self.vely * dt)

        if self.y < -300:
            return -1
        return 0


def main():
    window = gp.Window(900, 600, "Brick Breaker using goopylib!")
    window.background = (10, 5, 50)
    gp.set_buffer_swap_interval(0)
    window.resizable = True

    window.set_min_size(600, 400)
    window.set_aspect_ratio(900, 600)

    gp.Image(f"{PATH}/assets/background.png", (0, 0)).draw(window).set_transparency(0.4)

    controller = gp.Rectangle((0, -220), 120, 20).draw(window)
    controller.set_color((255, 255, 255))
    ball = Ball((random.randint(-450, 450), 20)).draw(window)

    blocks = []
    for i in range(900 // Brick.width):
        for j in range(4):
            blocks.append(Brick(i, j).draw(window))

    dt = 0.01

    while window.is_open():
        start = time.time()

        mousex, _ = window.to_world(*window.get_mouse_position())

        controller.x = max(-450, min(450, mousex))
        end = ball.update(dt, controller, blocks)

        if end or len(blocks) == 0:
            for i in range(100):
                controller.set_transparency(1 - i * 0.01)
                ball.set_transparency(1 - i * 0.01)
                for block in blocks:
                    block.set_transparency(1 - i * 0.01)

                time.sleep(0.005)
                gp.update()

            break

        gp.update()

        time.sleep(max(0, 0.01 - (time.time() - start)))


if __name__ == "__main__":
    main()

gp.terminate()
