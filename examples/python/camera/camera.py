import goopylib as gp


window = gp.Window(500, 500, "Camera")
camera = window.get_camera()

gp.Rectangle((0, 0), 200, 150).draw(window)

while window.is_open():
    gp.update()

    if window.check_key(gp.KEY_W):
        camera.y += 5
    elif window.check_key(gp.KEY_A):
        camera.x += 5
    elif window.check_key(gp.KEY_S):
        camera.move(0, -5)
    elif window.check_key(gp.KEY_D):
        camera.move(-5, 0)

    if window.check_key(gp.KEY_Q):
        camera.rotate(-3)
    elif window.check_key(gp.KEY_E):
        camera.rotation += 3


gp.terminate()
