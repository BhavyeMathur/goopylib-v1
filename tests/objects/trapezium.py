import goopylib as gp

window = gp.Window(500, 500)

quad = gp.Quad((-100, -100), (100, -100), (70, 50), (-70, 50))
quad.set_color((29, 146, 196), (50, 227, 209), (50, 227, 209), (50, 203, 245))
quad.draw(window)

while window.is_open():
    gp.update()

    if window.check_key(gp.KEY_ESCAPE):
        window.destroy()
        break

    if window.check_key(gp.KEY_W):
        quad.y += 3

    elif window.check_key(gp.KEY_A):
        quad.x -= 3

    elif window.check_key(gp.KEY_S):
        quad.move(0, -3)

    elif window.check_key(gp.KEY_D):
        quad.move(3, 0)

    if window.check_key(gp.KEY_E):
        quad.rotation += 3

    elif window.check_key(gp.KEY_Q):
        quad.rotate(-3)

    if window.check_key(gp.KEY_UP):
        quad.yscale *= 1.05
        quad.xscale *= 1.05

    elif window.check_key(gp.KEY_DOWN):
        quad.scale(0.95)

    if window.check_key(gp.KEY_H):
        if quad.is_hidden():
            quad.show()
        else:
            quad.hide()


gp.terminate()
