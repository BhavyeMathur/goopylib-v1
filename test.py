from goopylib.imports import *

window = GraphWin("Test Window", width=720, height=720, autoflush=False)

points = [Point(296, 468), Point(504, 468), Point(504, 520), Point(426, 520), Point(426, 598), Point(374, 598),
          Point(374, 520), Point(296, 520)]

def update_lines():
    window.destroy_all_lines()
    for i, p in enumerate(points):
        Line(p.get_anchor(), points[(i + 1) % len(points)].get_anchor(), outline_width=2,
             outline=LIGHTEST_NAVY_BLUE).draw(window)

    for line_points in TriangulateEarClipping([p.get_anchor() for p in points]):
        Line(line_points[0], line_points[1], outline=LIGHT_BLUE, outline_width=1).draw(window)

    #raise TypeError()


update_lines()

grad = [RED, GREEN] + [CHROME_YELLOW for _ in range(len(points) - 2)]
for i, p in enumerate(points):
    points[i] = Circle(p, radius=3, outline_width=0, layer=1, fill=grad[i], bounds=Circle(p, radius=50)) \
                .set_draggable(callback_x=update_lines).draw(window)

while True:
    mouse_pos = window.check_left_mouse_click()
    if mouse_pos is not None:
        print([p.get_anchor() for p in points])

    window.update_win()
