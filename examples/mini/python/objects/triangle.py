import goopylib as gp

window = gp.Window(500, 500)

triangle = gp.Triangle((-100, -100), (100, -100), (0, 50))
triangle.set_color((29, 146, 196), (50, 227, 209), (50, 203, 245))
triangle.draw(window)

while window.is_open():
    gp.update()

    if window.check_key(gp.KEY_ESCAPE):
        window.destroy()

    if window.check_key(gp.KEY_W):
        triangle.y += 3

    elif window.check_key(gp.KEY_A):
        triangle.x -= 3

    elif window.check_key(gp.KEY_S):
        triangle.move(0, -3)

    elif window.check_key(gp.KEY_D):
        triangle.move(3, 0)

    if window.check_key(gp.KEY_E):
        triangle.rotation += 3

    elif window.check_key(gp.KEY_Q):
        triangle.rotate(-3)

    if window.check_key(gp.KEY_UP):
        triangle.yscale *= 1.05
        triangle.xscale *= 1.05

    elif window.check_key(gp.KEY_DOWN):
        triangle.scale(0.95)

    if window.check_key(gp.KEY_H):
        if triangle.is_hidden():
            triangle.show()
        else:
            triangle.hide()

gp.terminate()
