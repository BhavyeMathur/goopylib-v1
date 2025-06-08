import goopylib as gp

window = gp.Window(500, 500)

circle = gp.Circle((-100, -100), 50)
circle.set_color((29, 146, 196), (50, 227, 209), (50, 227, 209), (50, 203, 245))
circle.draw(window)

while window.is_open():
    gp.update()

    if window.check_key(gp.KEY_ESCAPE):
        window.destroy()
        break

    if window.check_key(gp.KEY_W):
        circle.y += 3

    elif window.check_key(gp.KEY_A):
        circle.x -= 3

    elif window.check_key(gp.KEY_S):
        circle.move(0, -3)

    elif window.check_key(gp.KEY_D):
        circle.move(3, 0)

    if window.check_key(gp.KEY_E):
        circle.rotation += 3

    elif window.check_key(gp.KEY_Q):
        circle.rotate(-3)

    if window.check_key(gp.KEY_UP):
        circle.yscale *= 1.05
        circle.xscale *= 1.05

    elif window.check_key(gp.KEY_DOWN):
        circle.scale(0.95)

    if window.check_key(gp.KEY_H):
        if circle.is_hidden():
            circle.show()
        else:
            circle.hide()


gp.terminate()
