import goopylib as gp

window = gp.Window(500, 500)

rectangle = gp.Rectangle((-100, -100), (100, 50))
rectangle.set_color((29, 146, 196), (50, 227, 209), (50, 227, 209), (50, 203, 245))
rectangle.draw(window)

while window.is_open():
    gp.update()

    if window.check_key(gp.KEY_ESCAPE):
        window.destroy()
        break

    if window.check_key(gp.KEY_W):
        rectangle.y += 3

    elif window.check_key(gp.KEY_A):
        rectangle.x -= 3

    elif window.check_key(gp.KEY_S):
        rectangle.move(0, -3)

    elif window.check_key(gp.KEY_D):
        rectangle.move(3, 0)

    if window.check_key(gp.KEY_E):
        rectangle.rotation += 3

    elif window.check_key(gp.KEY_Q):
        rectangle.rotate(-3)

    if window.check_key(gp.KEY_UP):
        rectangle.yscale *= 1.05
        rectangle.xscale *= 1.05

    elif window.check_key(gp.KEY_DOWN):
        rectangle.scale(0.95)

    if window.check_key(gp.KEY_H):
        if rectangle.is_hidden():
            rectangle.show()
        else:
            rectangle.hide()


gp.terminate()
