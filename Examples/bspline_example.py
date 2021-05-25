from goopylib.imports import *

window = Window(title="B-Spline Curve Example Program", height=600, width=600)

control_points = [[70, 350], [200, 250], [400, 470], [300, 500], [230, 450], [120, 570]]
spline_points = []

resolution = 0.1

Line(*control_points, outline=RED).draw()

for point in control_points:
    Circle(point, 5, fill=RED, outline_width=0).draw()

for t in range(0, int(1 / resolution) * len(control_points)):
    t *= resolution
    spline_point = list(uniform_bspline(t, control_points, 2, is_open=False))
    spline_points.append(Circle(spline_point, 3, outline_width=0, layer=1).draw())

Line(*map(Circle.get_anchor, spline_points), outline=CHROME_YELLOW).draw()

while window.is_open():
    window.update()
