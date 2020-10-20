from goopylib.imports import *

window = Window(title="Test Window", width=700, height=700, bk_colour=ColourRGB(40, 40, 40))

Circle([350, 350], 10).draw(window)

while window.is_open():
    window.update()
