import goopylib as gp

window = gp.Window(500, 500)

ellipse = gp.Rectangle((-100, -100), (100, 50))
ellipse.set_color((29, 146, 196), (50, 227, 209), (50, 227, 209), (50, 203, 245))
ellipse.draw(window)

while window.is_open():
    gp.update()

    if window.check_key(gp.KEY_ESCAPE):
        window.destroy()

    if window.check_key(gp.KEY_W):
        ellipse.y += 3

    elif window.check_key(gp.KEY_A):
        ellipse.x -= 3

    elif window.check_key(gp.KEY_S):
        ellipse.move(0, -3)

    elif window.check_key(gp.KEY_D):
        ellipse.move(3, 0)

    if window.check_key(gp.KEY_E):
        ellipse.rotation += 3

    elif window.check_key(gp.KEY_Q):
        ellipse.rotate(-3)

    if window.check_key(gp.KEY_UP):
        ellipse.yscale *= 1.05
        ellipse.xscale *= 1.05

    elif window.check_key(gp.KEY_DOWN):
        ellipse.scale(0.95)

    if window.check_key(gp.KEY_H):
        if ellipse.is_hidden():
            ellipse.show()
        else:
            ellipse.hide()


gp.terminate()
