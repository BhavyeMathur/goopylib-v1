from goopylib.imports import *
from pathlib import Path as pathlib_Path

# I kinda wanted to scrap this, it wasn't that good.
def create_custom_ease():
    window = Window(title="goopylib: Create Custom Ease", width=get_screen_size()[1] * 0.7,
                    height=get_screen_size()[1] * 0.7, autoflush=False, bk_colour=DARKER_GREY)
    window.set_coords(0, 0, 1000, 1000)
    path = f"{pathlib_Path(__file__).parent.absolute()}/textures/"

    Image(Point(500, 500), f"{path}background.png").draw(window)

    add_button = Button(Image(Point(882, 219), f"{path}AddButton.png"),
                        Image(Point(882, 219), f"{path}AddButton.png").resize_factor(1.03),
                        Image(Point(882, 219), f"{path}AddButton.png").resize_factor(1.07),
                        Image(Point(882, 219), f"{path}AddButton.png").convert_greyscale()).draw(window)

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

                                  disabled_graphic=Image(Point(882, 428), f"{path}CustomTemplate.png")).draw(window)

    save_button = Button(Image(Point(882, 647), f"{path}SaveButton.png"),
                         Image(Point(882, 647), f"{path}SaveButton.png").resize_factor(1.03),
                         Image(Point(882, 647), f"{path}SaveButton.png").resize_factor(1.07)).draw(window)

    open_button = Button(Image(Point(882, 708), f"{path}OpenButton.png"),
                         Image(Point(882, 708), f"{path}OpenButton.png").resize_factor(1.03),
                         Image(Point(882, 708), f"{path}OpenButton.png").resize_factor(1.07)).draw(window)

    simulation_graphic1 = CycleButton(0, Rectangle(Point(50, 875), Point(125, 950), fill=LIGHTER_BLUE, outline_width=0),
                                      Circle(Point(88, 913), 38, fill=LIGHTER_BLUE, outline_width=0),
                                      autoflush=False).draw(window)

    simulation_graphic2 = CycleButton(0,
                                      Rectangle(Point(845, 845), Point(920, 920), fill=LIGHTER_BLUE, outline_width=0),
                                      Circle(Point(883, 883), 37.5, fill=LIGHTER_BLUE, outline_width=0),
                                      autoflush=False).draw(window)

    graph = Image(Point(500, 500), f"{path}Graph.png").draw(window)
    delete_dropdown = Button(Image(Point(0, 0), f"{path}DeleteDropdown.png"),
                             Image(Point(0, 0), f"{path}DeleteDropdownHover.png"))

    colour_grad = ColourGradient(LIGHTER_VIOLET, DARKEST_VIOLET, 100)

    resolution = 2

    control_points = [Circle(p, radius=10, fill=VIOLET, outline_width=0).draw(window) for p in
                      [Point(110, 673), Point(668, 118)]]
    last_control_points = control_points.copy()

    points = []
    for obj in control_points:
        points.append(obj.anchor)

    curve = []
    for t in range(int(10 ** resolution)):
        t /= 10 ** resolution
        curve.append(BezierCurve(t, points))

    circle_objects = []
    for i in range(int(10 ** resolution)):
        circle_objects.append(Circle(curve[i], radius=2, fill=colour_grad[i], outline_width=0).draw(window))

    selected_point = None
    selected_curve_point = None

    def ease(time):
        points = []
        for obj in control_points:
            points.append(obj.anchor)

        if interpolation_button.get_state() == 0:
            return 1 - (BezierCurve(time, points).y - 118) / 555
        else:
            return 1 - (LinearInterpolation(time, points).y - 118) / 555

    def update_curve():
        nonlocal circle_objects, curve, point, last_control_points, t, i

        points = []
        for obj in control_points:
            points.append(obj.anchor)

        curve = []
        for t in range(int(10 ** resolution)):
            t /= 10 ** resolution

            if interpolation_button.get_state() == 0:
                curve.append(BezierCurve(t, points))
            else:
                curve.append(LinearInterpolation(t, points))

        for i in range(int(10 ** resolution)):
            circle_objects[i].move_to_y(curve[i].y)

        last_control_points = control_points.copy()

    while True:
        t = time.time()
        mouse_pos = window.check_left_mouse_click()
        if mouse_pos is not None:
            if open_button.is_clicked(mouse_pos):
                filename = openfilebrowser()

            elif save_button.is_clicked(mouse_pos):
                filename = openfilebrowser()

            elif interpolation_button.is_clicked(mouse_pos):
                update_curve()

            elif play_button.is_clicked(mouse_pos):
                play_button.disable()

                """
                x = []
                for t in range(int(10 ** resolution)):
                    t /= 10 ** resolution
                    x.append(ease(t))
                plt.plot(x)
                plt.show()"""

                simulation_graphic1.glide_x(500, time=2, easing=ease)
                simulation_graphic2.animate_rotate(360, time=2, easing=ease)

            elif shape_button.is_clicked(mouse_pos):
                simulation_graphic1.set_state(shape_button.get_state())
                simulation_graphic2.set_state(shape_button.get_state())

            elif clear_button.is_clicked(mouse_pos):
                for point in control_points[1:-1]:
                    point.undraw()
                    control_points.remove(point)

            elif add_button.is_clicked(mouse_pos):
                add_button.disable()
                if selected_curve_point is None:
                    i = int((10 ** resolution / 2) * 2 ** (2 - len(control_points)))
                    control_points.insert(1, Circle(curve[i], radius=10, fill=colour_grad[i], outline_width=0).draw(
                        window))
                    control_points[1].set_draggable(callback=update_curve)
                else:
                    i = max(
                        math.ceil(circle_objects.index(selected_curve_point) / (100 / (len(control_points) - 1))) - 1,
                        1)
                    control_points.insert(i, Circle(selected_curve_point.get_anchor(), radius=10,
                                                    fill=colour_grad[circle_objects.index(selected_curve_point)],
                                                    outline_width=0).draw(window))
                    selected_curve_point = None
                    control_points[i].set_draggable(callback=update_curve)

                add_button.enable()

                template_button.disable()

            elif delete_dropdown.is_clicked(mouse_pos):
                delete_dropdown.undraw()
                selected_point.undraw()
                control_points.remove(selected_point)

                if len(control_points) == 2:
                    template_button.enable()

            else:
                for point in circle_objects:
                    if point.is_clicked(mouse_pos):
                        for i, p in enumerate(circle_objects):
                            p.set_fill(colour_grad[i])
                        point.set_fill(WHITE)
                        selected_curve_point = point
                        break

        if last_control_points != control_points:
            update_curve()

        if play_button.is_disabled and not simulation_graphic1.is_gliding:
            play_button.enable()

        mouse_pos = window.check_right_mouse_click()
        for point in control_points[1:-1]:
            if point.is_clicked(mouse_pos):
                delete_dropdown.draw(window).move_to_point(point.anchor, align="topleft")
                selected_point = point

        window.update_win()


def create_custom_ease2():
    window = Window(title="goopylib_b: Create Custom Ease", width=get_screen_size()[1] * 0.7,
                    height=get_screen_size()[1] * 0.7, autoflush=False, bk_colour=DARKER_GREY)
    window.set_coords(0, 0, 1000, 1000)
    path = f"{pathlib_Path(__file__).parent.absolute()}/textures/"

    while True:
        if window.is_closed():
            break

        window.update_win()

    window.close()
