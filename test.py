from goopylib.imports import *
import random

window = GraphWin("Test Window", width=2000, height=800, autoflush=False)

for circle in range(100):
    x_pos, y_pos = random.randint(50, window.get_width() - 50), random.randint(500, 750)
    fill = ColourRGB(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
    Rectangle(Point(x_pos - 30, y_pos - 30), Point(x_pos + 30, y_pos + 30), fill=fill).draw(window).glide_y(y_pos / 170, 0 - y_pos, easing=ease_bounce_out())

window.glide_y(time=2.5, dy=450, easing=ease_bounce_out())

while True:
    window.update_win()
