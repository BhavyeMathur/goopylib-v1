import goopylib as gp
from goopylib.scene.camera_controller import CameraController


window = gp.Window(500, 500, "Camera Controller")
controller = CameraController(window)

gp.Rectangle((0, 0), 200, 150).draw(window)

while window.is_open():
    gp.update()
    controller.update()


gp.terminate()
