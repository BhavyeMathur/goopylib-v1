from goopylib.imports import *

window = Window(title="Interpolation Curves Example Program", height=600, width=1200)

control_points = [[70, 50], [360, 300], [630, 260], [1130, 540]]
cosine_interpolated_points = []
cubic_interpolated_points = []
hermite_interpolated_points = []

resolution = 0.02

for point in control_points:
    Circle(point, 5, fill=RED).draw()

for t in range(int(1 / resolution) + 1):
    t *= resolution

    cosine_interpolated_points.append(cosine_curve(t, control_points))
    cubic_interpolated_points.append(cubic_curve(t, control_points))
    hermite_interpolated_points.append(hermite_curve(t, control_points, 0.5, 1))

Line(*control_points).draw()
CurvedLine(*control_points).draw()  # B-spline curve
CurvedLine(*cosine_interpolated_points, outline=BLUE).draw()
CurvedLine(*cubic_interpolated_points, outline=GREEN).draw()
CurvedLine(*hermite_interpolated_points, outline=PURPLE).draw()

while window.is_open():
    window.update()
