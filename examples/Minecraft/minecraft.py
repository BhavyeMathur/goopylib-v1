import goopylib as gp
import random

xN = 16
yN = 16

images = []


def set_transparency(i, j, val):
    if (0 <= i < xN) and (0 <= j < yN):
        images[xN * i + j].set_transparency(val)


def set_transparency4(i, j, v1, v2, v3, v4):
    if (0 <= i < xN) and (0 <= j < yN):
        images[xN * i + j].set_transparency(v1, v2, v3, v4)


def main():
    window = gp.Window(812, 812)
    window.background = (20, 20, 20)

    width = window.width / xN
    height = window.height / yN

    paths = ["assets/cobblestone.png",
             "assets/andesite.png",
             "assets/cracked_stone_bricks.png",
             "assets/stone.png",
             "assets/gravel.png",
             "assets/grass_block_top.png",
             "assets/coal_ore.png",
             "assets/iron_ore.png",
             "assets/copper_ore.png",
             "assets/diamond_ore.png",
             "assets/gold_ore.png",
             "assets/dead_tube_coral_block.png",
             "assets/dead_horn_coral_block.png",
             "assets/dead_bubble_coral_block.png",
             "assets/dead_brain_coral_block.png",
             "assets/stone_bricks.png",
             "assets/light_gray_concrete_powder.png"]

    for i in range(xN):
        x = width * i + width / 2 - 406

        for j in range(yN):
            y = height * j + height / 2 - 406

            img = gp.Image(random.choice(paths), (x, y), width, height).draw(window)
            images.append(img)

    while window.is_open():
        for img in images:
            img.set_transparency(0.1)

        x, y = window.get_mouse_position()
        x = int((x + 406) / width)
        y = int((y + 406) / height)

        set_transparency(x, y, 1)

        set_transparency4(x - 1, y, 0.5, 1, 1, 0.5)
        set_transparency4(x + 1, y, 1, 0.5, 0.5, 1)
        set_transparency4(x, y - 1, 0.5, 0.5, 1, 1)
        set_transparency4(x, y + 1, 1, 1, 0.5, 0.5)

        set_transparency4(x - 1, y - 1, 0.3, 0.5, 1, 0.5)
        set_transparency4(x - 1, y + 1, 0.5, 1, 0.5, 0.3)
        set_transparency4(x + 1, y - 1, 0.5, 0.3, 0.5, 1)
        set_transparency4(x + 1, y + 1, 1, 0.5, 0.3, 0.5)

        set_transparency4(x - 2, y, 0.1, 0.5, 0.5, 0.1)
        set_transparency4(x + 2, y, 0.5, 0.1, 0.1, 0.5)
        set_transparency4(x, y - 2, 0.1, 0.1, 0.5, 0.5)
        set_transparency4(x, y + 2, 0.5, 0.5, 0.1, 0.1)

        set_transparency4(x - 2, y + 1, 0.1, 0.5, 0.3, 0.1)
        set_transparency4(x - 2, y - 1, 0.1, 0.3, 0.5, 0.1)
        set_transparency4(x + 2, y + 1, 0.5, 0.1, 0.1, 0.3)
        set_transparency4(x + 2, y - 1, 0.3, 0.1, 0.1, 0.5)

        set_transparency4(x - 1, y - 2, 0.1, 0.1, 0.5, 0.3)
        set_transparency4(x + 1, y - 2, 0.1, 0.1, 0.3, 0.5)
        set_transparency4(x - 1, y + 2, 0.3, 0.5, 0.1, 0.1)
        set_transparency4(x + 1, y + 2, 0.5, 0.3, 0.1, 0.1)

        set_transparency4(x - 2, y - 2, 0.1, 0.1, 0.2, 0.1)
        set_transparency4(x + 2, y - 2, 0.1, 0.1, 0.1, 0.3)
        set_transparency4(x - 2, y + 2, 0.1, 0.3, 0.1, 0.1)
        set_transparency4(x + 2, y + 2, 0.2, 0.1, 0.1, 0.1)

        gp.update()


if __name__ == "__main__":
    main()
    gp.terminate()
