from goopylib.imports import *

window = GraphWin("Test Window", x_pos=0, width=800, height=800, autoflush=False)

window.glide(time=5, dy=450, dx=500, easing_y=ease_elastic_out())
window.glide_x(time=5, dx=400)

while True:
    window.update_win()
