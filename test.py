from goopylib.imports import *

window = GraphWin("Test Window", x_pos=0, width=800, height=800, autoflush=False)
"""
for y_pos in range(30, 770, 45):
    gradient = ColourGradient(colour_start=RandomColour(), colour_end=RandomColour(), divisions=len(range(30, 770, 45)))
    for i, x_pos in enumerate(range(30, 770, 45)):
        Rectangle(Point(x_pos - 20, y_pos - 20), Point(x_pos + 20, y_pos + 20), fill=gradient[i]).draw(window)
"""

"""
rect_size = 5
gap = 1
gradient = ColourGradient2D(RandomColour(), RandomColour(), RandomColour(), RandomColour(),
                            divisions_x=len(range(30, 770, rect_size * 2 + gap)),
                            divisions_y=len(range(30, 770, rect_size * 2 + gap)))

for i, y_pos in enumerate(range(30, 770, rect_size * 2 + gap)):
    for j, x_pos in enumerate(range(30, 770, rect_size * 2 + gap)):
        Rectangle(Point(x_pos - rect_size, y_pos - rect_size),
                  Point(x_pos + rect_size, y_pos + rect_size), fill=gradient[j][i], outline_width=0).draw(window)
"""

Rectangle(Point(10, 10), Point(100, 30), outline_width=0, fill=ColourRGB(0, 255, 0)).draw(window)
Text(Point(55, 20), "rgb(0, 255, 0)", font_colour=WHITE, font_size=12, font_style="bold").draw(window)

while True:
    window.update_win()
