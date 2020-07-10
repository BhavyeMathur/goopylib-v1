from goopylib.imports import *
from pathlib import Path as pathlib_Path


def create_custom_ease():
    window = GraphWin(title="goopylib: Create Custom Ease", width=get_screen_size()[1] * 0.7,
                      height=get_screen_size()[1] * 0.7, autoflush=False, bk_colour=DARKER_GREY)
    window.set_coords(0, 0, 1000, 1000)
    path = f"{pathlib_Path(__file__).parent.absolute()}/textures/"

    Image(Point(500, 500), f"{path}background.png").draw(window)

    add_button = Button(Image(Point(882, 219), f"{path}AddButton.png"),
                        Image(Point(882, 219), f"{path}AddButton.png").resize_factor(1.03),
                        Image(Point(882, 219), f"{path}AddButton.png").resize_factor(1.07)).draw(window)

    clear_button = Button(Image(Point(882, 280), f"{path}ClearButton.png"),
                          Image(Point(882, 280), f"{path}ClearButton.png").resize_factor(1.03),
                          Image(Point(882, 280), f"{path}ClearButton.png").resize_factor(1.07)).draw(window)

    play_button = Button(Image(Point(256, 805), f"{path}PlayButton.png"),
                         Image(Point(256, 805), f"{path}PlayButton.png").resize_factor(1.03),
                         Image(Point(256, 805), f"{path}PlayButton.png").resize_factor(1.07)).draw(window)

    shape_button = CycleButton(0,
                              Button(Image(Point(99, 805), f"{path}RectangleButton.png"),
                                     Image(Point(99, 805), f"{path}RectangleButton.png").resize_factor(1.03),
                                     Image(Point(99, 805), f"{path}RectangleButton.png").resize_factor(1.07)),

                              Button(Image(Point(99, 805), f"{path}CircleButton.png"),
                                     Image(Point(99, 805), f"{path}CircleButton.png").resize_factor(1.03),
                                     Image(Point(99, 805), f"{path}CircleButton.png").resize_factor(1.07))) \
        .draw(window)

    interpolation_button = CycleButton(0,
                                       Button(Image(Point(882, 109), f"{path}BezierButton.png"),
                                              Image(Point(882, 109), f"{path}BezierButton.png").resize_factor(1.03),
                                              Image(Point(882, 109), f"{path}BezierButton.png").resize_factor(1.07)),

                                       Button(Image(Point(882, 109), f"{path}CubicButton.png"),
                                              Image(Point(882, 109), f"{path}CubicButton.png").resize_factor(1.03),
                                              Image(Point(882, 109), f"{path}CubicButton.png").resize_factor(1.07)),

                                       Button(Image(Point(882, 109), f"{path}LinearButton.png"),
                                              Image(Point(882, 109), f"{path}LinearButton.png").resize_factor(1.03),
                                              Image(Point(882, 109), f"{path}LinearButton.png").resize_factor(1.07))) \
        .draw(window)

    template_button = CycleButton(0,
                                  Button(Image(Point(882, 411), f"{path}LinearTemplate.png"),
                                         Image(Point(882, 411), f"{path}LinearTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}LinearTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}BackTemplate.png"),
                                         Image(Point(882, 411), f"{path}BackTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}BackTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}ExponentialTemplate.png"),
                                         Image(Point(882, 411), f"{path}ExponentialTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}ExponentialTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}PolynomialTemplate.png"),
                                         Image(Point(882, 411), f"{path}PolynomialTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}PolynomialTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}SineTemplate.png"),
                                         Image(Point(882, 411), f"{path}SineTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}SineTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}CircleTemplate.png"),
                                         Image(Point(882, 411), f"{path}CircleTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}CircleTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}ElasticTemplate.png"),
                                         Image(Point(882, 411), f"{path}ElasticTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}ElasticTemplate.png").resize_factor(1.07)),

                                  Button(Image(Point(882, 411), f"{path}BounceTemplate.png"),
                                         Image(Point(882, 411), f"{path}BounceTemplate.png").resize_factor(1.03),
                                         Image(Point(882, 411), f"{path}BounceTemplate.png").resize_factor(1.07)),

                                  disabled_graphic=Image(Point(882, 428), f"{path}CustomTemplate.png") ).draw(window)

    save_button = Button(Image(Point(882, 647), f"{path}SaveButton.png"),
                         Image(Point(882, 647), f"{path}SaveButton.png").resize_factor(1.03),
                         Image(Point(882, 647), f"{path}SaveButton.png").resize_factor(1.07)).draw(window)

    open_button = Button(Image(Point(882, 708), f"{path}OpenButton.png"),
                         Image(Point(882, 708), f"{path}OpenButton.png").resize_factor(1.03),
                         Image(Point(882, 708), f"{path}OpenButton.png").resize_factor(1.07)).draw(window)

    simulation_graphic1 = CycleButton(0, Rectangle(Point(50, 875), Point(125, 950), fill=LIGHTER_BLUE, outline_width=0),
                                      Circle(Point(88, 913), 38, fill=LIGHTER_BLUE, outline_width=0),
                                      autoflush=False).draw(window)

    simulation_graphic2 = CycleButton(0, Rectangle(Point(845, 845), Point(920, 920), fill=LIGHTER_BLUE, outline_width=0),
                                      Circle(Point(883, 883), 37.5, fill=LIGHTER_BLUE, outline_width=0),
                                      autoflush=False).draw(window)

    graph = Image(Point(500, 500), f"{path}Graph.png").draw(window)

    control_points = [Point(110, 673), Point(668, 118)]
    last_control_points = []
    point_graphics = [Circle(p, radius=10, fill=VIOLET, outline_width=0).draw(window) for p in control_points]

    curve = []
    circle_objects = []

    resolution = 2

    def update_curve():
        global curve, point, last_control_points
        for point in circle_objects:
            point.undraw()

        curve = []
        for t in range(10 ** resolution):
            t /= 10 ** resolution
            curve.append(BezierCurve(t, control_points))

        for point in curve:
            circle_objects.append(Circle(point, radius=2, fill=VIOLET, outline_width=0).draw(window))

        last_control_points = control_points.copy()
        return curve

    while True:
        mouse_pos = window.check_left_mouse_click()
        if open_button.is_clicked(mouse_pos):
            filename = openfilebrowser()

        elif save_button.is_clicked(mouse_pos):
            filename = openfilebrowser()

        elif play_button.is_clicked(mouse_pos):
            pass

        elif clear_button.is_clicked(mouse_pos):
            control_points = [Point(110, 673), Point(668, 118)]
            for point in point_graphics:
                point.undraw()
            point_graphics = [Circle(p, radius=10, fill=VIOLET, outline_width=0).draw(window) for p in control_points]

        elif add_button.is_clicked(mouse_pos):
            print(int(50 * 2 ** (2 - len(control_points))), len(curve))
            control_points.insert(1, curve[int(50 * 2 ** (2 - len(control_points)))])
            point_graphics.append(Circle(control_points[1], radius=10, fill=VIOLET, outline_width=0).draw(window))
            point_graphics[-1].set_draggable(callback=update_curve)

        simulation_graphic1.set_state(shape_button.get_state())
        simulation_graphic2.set_state(shape_button.get_state())

        if last_control_points != control_points:
            curve = update_curve()

        window.update_win()
