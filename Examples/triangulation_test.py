from goopylib.imports import *

window = Window(title="Polygon Triangulation Test", width=700, height=700)

vertices = [[100, 600], [350.0, 100.0], [558.0, 20.0], [681.0, 72.0], [636.0, 139.0],
            [677.0, 235.0], [644.0, 368.0], [666.0, 486.0], [630.0, 599.0], [544.0, 659.0],
            [488.0, 622.0], [543.0, 628.0], [572.0, 601.0], [592.0, 554.0], [631.0, 515.0],
            [296.0, 583.0]]

if False:
    while True:
        print(timeit.timeit(
            setup="from __main__ import vertices; from goopylib.maths.Triangulation import triangulate_earclip",
            stmt="triangulate_earclip(vertices)", number=1000))
        print(timeit.timeit(
            setup="from __main__ import vertices; from goopylib.maths.Triangulation import triangulate_modified_earclip",
            stmt="triangulate_modified_earclip(vertices)", number=1000))

        print()

circles = [Circle(vertex, radius=4, outline_width=0).set_draggable().set_movement_bounds(window).draw() for vertex in vertices]

def draw_lines():
    triangulation = triangulate_modified_earclip(vertices)

    window.destroy_all_lines()
    for triangle in triangulation:
        for i, vertex in enumerate(triangle):
            Line(vertex, triangle[i - 1]).draw()


draw_lines()

while window.is_open():
    mouse_pos = window.check_right_mouse_click()
    if mouse_pos is not None:
        vertices.append(mouse_pos)
        circles.append(Circle(mouse_pos, radius=4, outline_width=0).set_draggable().set_movement_bounds(window).draw())
        draw_lines()
        print(vertices)

    for i, obj in enumerate(circles):
        if obj.has_moved():
            vertices[i] = obj.get_anchor()
            draw_lines()

    window.update()
