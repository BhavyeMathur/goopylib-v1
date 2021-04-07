import math

from manim import *

# cd Documentation/YouTube/"BezierCurves #1"
# manim video_scenes.py SCENENAME -pql
# é

"""
Scene_2 - What are Bézier Curves 
Scene_3 - The Logic Behind Bézier Curves 
Scene_4 - Conclusion
"""

config.background_color = DARKER_GREY

def distance_formula(p1, p2):
    return ((p2[0] - p1[0]) ** 2 + (p2[1] - p1[1]) ** 2) ** 0.5


def linear_curve(t, control_points):
    number_of_points = len(control_points)
    total_distance = sum(
        distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

    points_interval = 1 / (number_of_points - 1)
    next_point = math.ceil(t / points_interval)

    mu = (t - (points_interval * (next_point - 1))) / points_interval
    mu2 = 1 - mu

    previous_point = control_points[next_point - 1]
    next_point = control_points[next_point]

    return [mu2 * previous_point[0] + mu * next_point[0], mu2 * previous_point[1] + mu * next_point[1]]


def cosine_curve(t, control_points):
    number_of_points = len(control_points)
    total_distance = sum(
        distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

    points_interval = 1 / (number_of_points - 1)
    next_point = math.ceil(t / points_interval)

    mu = (t - (points_interval * (next_point - 1))) / points_interval

    previous_point = control_points[next_point - 1]
    next_point = control_points[next_point]

    mu2 = (1 - math.cos(mu * math.pi)) / 2

    return [(1 - mu) * previous_point[0] + mu * next_point[0], (1 - mu2) * previous_point[1] + mu2 * next_point[1]]


def cubic_curve(t, control_points):
    number_of_points = len(control_points)
    total_distance = sum(distance_formula(control_points[point - 1], control_points[point]) for point in range(number_of_points))

    points_interval = 1 / (number_of_points - 1)
    next_point = math.ceil(t / points_interval)

    mu = (t - (points_interval * (next_point - 1))) / points_interval

    previous_point = control_points[next_point - 1]
    previous_previous_point = control_points[next_point - 2]
    next_next_point = control_points[(next_point + 1) % number_of_points]
    next_point = control_points[next_point]

    a0 = next_next_point[1] - next_point[1] - previous_previous_point[1] + previous_point[1]
    a1 = previous_previous_point[1] - previous_point[1] - a0
    a2 = next_point[1] - previous_previous_point[1]
    a3 = previous_point[1]

    return [(1 - mu) * previous_point[0] + mu * next_point[0], (a0 * mu ** 3) + (a1 * mu ** 2) + (a2 * mu) + a3]


def bezier_curve(t, control_points):
    size = len(control_points)
    sum_x, sum_y = 0, 0

    size = len(control_points) - 1
    for i in range(0, size + 1):
        coeff = bernstein_polynomial(i, size, t)
        sum_y += coeff * control_points[i][1]
        sum_x += coeff * control_points[i][0]

    return [sum_x, sum_y]


def bernstein_polynomial(i, n, t):
    return combination(n, i) * (t ** i) * ((1 - t) ** (n - i))


def combination(n, k):
    return math.factorial(n) / (math.factorial(k) * math.factorial(n - k))


class Scene_2_1(Scene):
    def construct(self):
        P1_text = Text("P1", color=BLACK, size=0.5).shift(4 * LEFT, 2 * DOWN)
        P2_text = Text("P2", color=BLACK, size=0.5).shift(4 * RIGHT, 2 * UP)
        P1 = Dot(radius=0.2 + P1_text.get_width() / 2).move_to(P1_text.get_center())
        P2 = P1.copy().move_to(P2_text.get_center())
        points = VGroup(P1, P2)
        points_text = VGroup(P1_text, P2_text)
        points_group = VGroup(P1, P1_text, P2, P2_text)

        drawn_curve1 = ArcBetweenPoints(P2.get_center(), P1.get_center(), color=GOLD)
        linear_interpolation1 = Line(P2.get_center(), P1.get_center(), color=RED_C)

        question_text = Text("Construct a Curve between P1 and P2", t2c={'[22:24]': TEAL_D, '[27:]': TEAL_D})
        curve_text = Text("\"curve\"", slant=ITALIC, size=0.5).shift(3 * RIGHT, DOWN)

        dot = Dot(linear_interpolation1.get_center()).shift(0.5 * DOWN, 0.5 * RIGHT)
        curve_text_arrow = CurvedArrow(curve_text.get_left(), dot.get_center(), angle=-1).shift(0.4 * LEFT)

        self.play(Create(points_group))
        self.play(Write(question_text))

        question_text.generate_target()
        question_text.target.scale(0.7)
        question_text.target.next_to(P1, RIGHT)
        question_text.target.shift(2 * RIGHT, DOWN)
        self.play(MoveToTarget(question_text))

        self.bring_to_back(points)
        self.bring_to_back(drawn_curve1)
        self.play(Create(drawn_curve1), points.animate.set_fill(GOLD))

        self.wait(2)

        self.bring_to_back(linear_interpolation1)
        self.play(Create(linear_interpolation1), points.animate.set_fill(RED_C), drawn_curve1.animate.set_color(WHITE))

        self.wait(1)

        self.play(Write(curve_text), Create(curve_text_arrow))

        self.wait(5)


class Scene_2_2(Scene):
    def construct(self):
        P1_text = Text("P1", color=BLACK, size=0.5).shift(4 * LEFT, 2 * DOWN)
        P2_text = Text("P2", color=BLACK, size=0.5).shift(4 * RIGHT, 2 * UP)
        P1 = Dot(radius=0.2 + P1_text.get_width() / 2, color=RED_C).move_to(P1_text.get_center())
        P2 = P1.copy().move_to(P2_text.get_center())

        points_text = VGroup(P1_text, P2_text)
        points_group = VGroup(P1, P1_text, P2, P2_text)

        drawn_curve1 = ArcBetweenPoints(P2.get_center(), P1.get_center())
        linear_interpolation1 = Line(P2.get_center(), P1.get_center(), color=RED_C)

        question_text = Text("Construct a Curve between P1 and P2", t2c={'[22:24]': TEAL_D, '[27:]': TEAL_D}) \
            .scale(0.7).next_to(P1, RIGHT).shift(2 * RIGHT, DOWN)
        curve_text = Text("\"curve\"", slant=ITALIC, size=0.5).shift(3 * RIGHT, DOWN)

        dot = Dot(linear_interpolation1.get_center()).shift(0.5 * DOWN, 0.5 * RIGHT)
        curve_text_arrow = CurvedArrow(curve_text.get_left(), dot.get_center(), angle=-1).shift(0.4 * LEFT)

        self.add(linear_interpolation1, drawn_curve1, points_group, question_text, curve_text, curve_text_arrow)

        # --------------------------------

        self.play(FadeOut(drawn_curve1), FadeOut(curve_text), FadeOut(curve_text_arrow))

        new_P1 = P1.copy().shift(0.5 * LEFT)
        new_P1_text = P1_text.copy().move_to(new_P1.get_center())
        new_P2 = P2.copy().shift(3.5 * LEFT)
        new_P2_text = P2_text.copy().move_to(new_P2.get_center())

        P3_text = Text("P3", color=BLACK, size=0.5).move_to(P2_text.get_center())
        new_P3_text = P3_text.copy().shift(0.5 * RIGHT, 2.5 * DOWN)
        points_text.add(P3_text)

        P3 = P2.copy()
        new_P3 = P3.copy().move_to(new_P3_text.get_center())

        new_curve2 = Line(new_P2.get_center(), new_P1.get_center(), color=RED_C)

        new_question_text = Text("Construct a Curve between P1, P2, P3", t2c={'[22:24]': TEAL_D,
                                                                              '[25:27]': TEAL_D,  '[28:30]': TEAL_D}) \
            .scale(0.7).next_to(P1, RIGHT).shift(2 * RIGHT, DOWN)

        self.bring_to_back(P3, P3_text)
        self.play(Transform(P1, new_P1), Transform(P1_text, new_P1_text),
                  Transform(P3, new_P3), Transform(P3_text, new_P3_text),
                  Transform(P2, new_P2), Transform(P2_text, new_P2_text),
                  Transform(linear_interpolation1, new_curve2), Transform(question_text, new_question_text))

        linear_interpolation2 = Line(P3.get_center(), P2.get_center(), color=RED_C)
        self.bring_to_back(linear_interpolation2)
        self.play(Create(linear_interpolation2))

        self.wait(1)

        drawn_curve2 = VMobject().set_points_smoothly([P1.get_center(), P2.get_center(), P3.get_center()])
        self.bring_to_back(drawn_curve2)
        self.play(Create(drawn_curve2))

        # Creating the 2 Smaller Interpolation Graphs -----

        interpolation1 = VGroup(P1, P2, P3, points_text)
        interpolation1.generate_target()
        interpolation1.target.scale(0.4).shift(3 * LEFT)

        interpolation2 = interpolation1.copy()
        interpolation2.target.shift(6 * RIGHT)

        divider = Line([0, 2, 0], [0, -2, 0])

        # Adding the Interpolation Titles ------

        title1 = Text("Cosine Interpolation").next_to(interpolation1, UP)
        title2 = Text("Cubic Interpolation").next_to(interpolation2, UP)
        interpolation1.add(title1)
        interpolation2.add(title2)
        interpolation1.target.add(Text("Cosine Interpolation", size=0.4).next_to(interpolation1.target, UP))
        interpolation2.target.add(Text("Cubic Interpolation", size=0.4).next_to(interpolation2.target, UP))

        # Sine and Cubic Curves -------

        points = [cosine_curve(t / 20, [P1.get_center(), P2.get_center(), P3.get_center()]) + [0] for t in range(21)]
        drawn_sine = VMobject().set_points_smoothly(points).scale(0.4).shift(3 * LEFT)

        points = [cubic_curve(t / 20, [P1.get_center(), P2.get_center(), P3.get_center()]) + [0] for t in range(21)]
        drawn_cubic = VMobject().set_points_smoothly(points).scale(0.4).shift(3 * RIGHT)

        interpolation1.submobjects.insert(0, drawn_curve2)
        interpolation2.submobjects.insert(0, drawn_curve2.copy())
        interpolation1.target.submobjects.insert(0, drawn_sine)
        interpolation2.target.submobjects.insert(0, drawn_cubic)

        # Changing the Linear Interpolation to a curve ------

        drawn_curve3 = VMobject().set_points_smoothly([P3.get_center(), P2.get_center(), P1.get_center()])
        drawn_curve3.scale(0.4).shift(3 * LEFT).set_color(RED_C)
        drawn_curve4 = drawn_curve3.copy().shift(6 * RIGHT)

        dashed_drawn_curve3 = DashedVMobject(drawn_curve3)
        dashed_drawn_curve4 = DashedVMobject(drawn_curve4)
        dashed_linear1 = DashedVMobject(linear_interpolation1)
        dashed_linear2 = DashedVMobject(linear_interpolation2)

        linear_interpolation1.generate_target()
        linear_interpolation1.target = drawn_curve3
        linear_interpolation1.target.set_stroke(opacity=0)

        linear_interpolation2.generate_target()
        linear_interpolation2.target = drawn_curve4
        linear_interpolation2.target.set_stroke(opacity=0)

        self.bring_to_back(dashed_linear1, dashed_linear2)
        self.play(FadeOut(question_text), Create(divider), FadeIn(title1), FadeIn(title2),
                  MoveToTarget(interpolation1), MoveToTarget(interpolation2),
                  MoveToTarget(linear_interpolation1), MoveToTarget(linear_interpolation2),
                  Transform(dashed_linear1, dashed_drawn_curve3),
                  Transform(dashed_linear2, dashed_drawn_curve4))

        self.wait(5)


class Scene_2_3(Scene):
    def construct(self):
        color2 = TEAL_D
        color3 = BLUE_D

        P1_text = Text("P1", color=BLACK, size=0.5).shift(4.5 * LEFT, 2 * DOWN)
        P2_text = Text("P2", color=BLACK, size=0.5).shift(0.5 * RIGHT, 2 * UP)
        P3_text = Text("P3", color=BLACK, size=0.5).shift(4.5 * RIGHT, 0.5 * DOWN)
        P1 = Dot(radius=0.2 + P1_text.get_width() / 2, color=RED_C).move_to(P1_text.get_center())
        P2 = P1.copy().move_to(P2_text.get_center())
        P3 = P1.copy().move_to(P3_text.get_center())
        points_group = VGroup(P1, P1_text, P2, P2_text, P3, P3_text)

        drawn_curve2 = DashedVMobject(VMobject().set_points_smoothly([P1.get_center(),
                                                                      P2.get_center(),
                                                                      P3.get_center()]).set_color(RED_C))

        # Creating the 2 Smaller Interpolation Graphs -----

        interpolation1 = VGroup(drawn_curve2, points_group)
        interpolation2 = interpolation1.copy()

        points = [bezier_curve(t / 20, [P1.get_center(), P2.get_center(), P3.get_center()]) + [0] for t in range(21)]
        drawn_bezier = VMobject().set_points_smoothly(points)

        bezier_interpolation = VGroup(drawn_bezier, points_group).copy().scale(0.8).shift(2 * RIGHT)
        bezier_interpolation[1][0].set_color(color2)
        bezier_interpolation[1][2].set_color(color2)
        bezier_interpolation[1][4].set_color(color2)

        # Sine and Cubic Curves -------

        points = [cosine_curve(t / 20, [P1.get_center(), P2.get_center(), P3.get_center()]) + [0] for t in range(21)]
        drawn_sine = VMobject().set_points_smoothly(points)

        points = [cubic_curve(t / 20, [P1.get_center(), P2.get_center(), P3.get_center()]) + [0] for t in range(21)]
        drawn_cubic = VMobject().set_points_smoothly(points)

        interpolation1.submobjects.insert(1, drawn_sine)
        interpolation2.submobjects.insert(1, drawn_cubic)

        divider = Line([0, 2, 0], [0, -2, 0])

        self.add(divider, interpolation1.scale(0.4).shift(3 * LEFT), interpolation2.scale(0.4).shift(3 * RIGHT))

        title1 = Text("Cosine Interpolation", size=0.4).next_to(interpolation1, UP)
        title2 = Text("Cubic Interpolation", size=0.4).next_to(interpolation2, UP)
        interpolation1.add(title1)
        interpolation2.add(title2)

        interpolation1.generate_target()
        interpolation2.generate_target()

        # -------------------------------

        divider.generate_target()

        interpolation1.target.scale(0.8).shift(2 * LEFT, 1.7 * UP)
        interpolation2.target.scale(0.8).move_to(interpolation1.target.get_center()).shift(4 * DOWN)
        divider.target = Line([0, 0, 0], [3, 0, 0]).move_to(interpolation1.target.get_center()).set_y(0)

        self.play(MoveToTarget(interpolation1), MoveToTarget(interpolation2), MoveToTarget(divider))

        control_points_text = Text("control points", size=0.4, color=color2)
        control_points_text.next_to(bezier_interpolation[1][0], DOWN).shift(2 * RIGHT)

        arrow1 = Arrow(control_points_text.get_left(), bezier_interpolation[1][0].get_corner(DOWN + RIGHT),
                       stroke_width=1, tip_length=0.1)
        arrow2 = Arrow(control_points_text.get_right(), bezier_interpolation[1][4].get_corner(DOWN + LEFT),
                       stroke_width=1, tip_length=0.1)

        self.play(Create(bezier_interpolation))
        self.play(Write(control_points_text), Create(arrow1), Create(arrow2))
        self.wait(1)

        start_text = Text("start", size=0.4, color=color3).next_to(arrow1.get_start(), RIGHT)

        end_text = control_points_text.copy().move_to(control_points_text.get_center())
        new_end_text = Text("end", size=0.4, color=color3).next_to(bezier_interpolation[1][4], DOWN).shift(1.5 * LEFT)

        new_arrow2 = Arrow(new_end_text.get_right(), bezier_interpolation[1][4].get_corner(DOWN + LEFT),
                           stroke_width=1, tip_length=0.1, color=color3)

        arrow3 = Arrow(bezier_curve(0.54, [bezier_interpolation[1][0].get_center(),
                                           bezier_interpolation[1][2].get_center(),
                                           bezier_interpolation[1][4].get_center()]) + [0],
                       bezier_interpolation[1][2].get_bottom(), color=color2)

        self.play(bezier_interpolation[1][0].animate.set_color(color3), Create(arrow3),
                  bezier_interpolation[1][4].animate.set_color(color3), Transform(control_points_text, start_text),
                  Transform(arrow2, new_arrow2), Transform(end_text, new_end_text), arrow1.animate.set_color(color3))
        start_text = control_points_text

        # ----------

        P1_text = bezier_interpolation[1][1]
        P1_dot = bezier_interpolation[1][0]
        P1 = VGroup(P1_dot, P1_text)

        P2_text = bezier_interpolation[1][3]
        P2_dot = bezier_interpolation[1][2]
        P2 = VGroup(P2_dot, P2_text)

        P3_text = bezier_interpolation[1][5]
        P3_dot = bezier_interpolation[1][4]
        P3 = VGroup(P3_dot, P3_text)

        # ----------------

        bezier_group = VGroup(bezier_interpolation, arrow1, arrow2, arrow3, start_text, end_text)
        bezier_group.generate_target()
        bezier_group.target.shift(2 * LEFT).scale(1.25)

        self.play(divider.animate.shift(4 * LEFT), interpolation1.animate.shift(4 * LEFT),
                  interpolation2.animate.shift(4 * LEFT), MoveToTarget(bezier_group))

        P4_text = Text("P4", color=BLACK, size=0.5).shift(4.5 * RIGHT, 0.5 * DOWN)
        P4_dot = P3_dot.copy().move_to(P4_text.get_center())
        P4 = VGroup(P4_dot, P4_text)

        new_P2 = P2.copy().shift(3 * LEFT).scale(0.4)
        new_P3 = P3.copy().shift(2 * LEFT, DOWN).scale(0.4)
        new_P3[0].set_color(color2)
        new_P4 = P4.copy().shift(2 * UP)

        points = [bezier_curve(t / 30, [P1.get_center(), new_P2.get_center(), new_P3.get_center(),
                                        new_P4.get_center()]) + [0] for t in range(31)]

        bezier_interpolation[0].generate_target()
        bezier_interpolation[0].target = VMobject().set_points_smoothly(points)

        self.add(P4)
        self.play(Transform(P2, new_P2), Transform(P4, new_P4), Transform(P3, new_P3), Unwrite(start_text),
                  MoveToTarget(bezier_interpolation[0]), Uncreate(arrow1), Uncreate(arrow2), Uncreate(arrow3),
                  Unwrite(end_text))

        bezier_line1 = Line(P1.get_center(), P2.get_center()).set_stroke(width=3).set_color([color3, color2])
        bezier_line2 = Line(P4.get_center(), P3.get_center()).set_stroke(width=3).set_color([color2, color3])

        self.bring_to_back(bezier_line1, bezier_line2)
        self.play(Create(bezier_line1), Create(bezier_line2))

        new_P2 = P2.copy().shift(2 * RIGHT)
        new_P3 = P3.copy().shift(2 * RIGHT)
        new_bezier_line1 = Line(P1.get_center(), new_P2.get_center()).set_stroke(width=3).set_color([color3, color2])
        new_bezier_line2 = Line(P4.get_center(), new_P3.get_center()).set_stroke(width=3).set_color([color2, color3])
        points = [bezier_curve(t / 30, [P1.get_center(), new_P2.get_center(), new_P3.get_center(),
                                        P4.get_center()]) + [0] for t in range(31)]
        new_bezier = VMobject().set_points_smoothly(points)

        self.play(Transform(P2, new_P2), Transform(P3, new_P3), Transform(bezier_line1, new_bezier_line1),
                  Transform(bezier_line2, new_bezier_line2), Transform(bezier_interpolation[0], new_bezier))

        new_P3 = P3.copy().shift(2 * RIGHT)
        new_bezier_line2 = Line(P4.get_center(), new_P3.get_center()).set_stroke(width=3).set_color([color2, color3])
        points = [bezier_curve(t / 30, [P1.get_center(), new_P2.get_center(), new_P3.get_center(),
                                        P4.get_center()]) + [0] for t in range(31)]
        new_bezier = VMobject().set_points_smoothly(points)

        self.play(Transform(P3, new_P3), Transform(bezier_line2, new_bezier_line2), Transform(bezier_interpolation[0],
                                                                                              new_bezier))

        new_P3 = P3.copy().shift(4 * LEFT)
        new_bezier_line2 = Line(P4.get_center(), new_P3.get_center()).set_stroke(width=3).set_color([color2, color3])
        points = [bezier_curve(t / 30, [P1.get_center(), new_P2.get_center(), new_P3.get_center(),
                                        P4.get_center()]) + [0] for t in range(31)]
        new_bezier = VMobject().set_points_smoothly(points)

        self.play(Transform(P3, new_P3), Transform(bezier_line2, new_bezier_line2), Transform(bezier_interpolation[0],
                                                                                              new_bezier))

        new_P2 = P2.copy().shift(2 * LEFT)
        new_P3 = P3.copy().shift(2 * LEFT)
        new_bezier_line1 = Line(P1.get_center(), new_P2.get_center()).set_stroke(width=3).set_color([color3, color2])
        new_bezier_line2 = Line(P4.get_center(), new_P3.get_center()).set_stroke(width=3).set_color([color2, color3])
        points = [bezier_curve(t / 30, [P1.get_center(), new_P2.get_center(), new_P3.get_center(),
                                        P4.get_center()]) + [0] for t in range(31)]
        new_bezier = VMobject().set_points_smoothly(points)

        self.play(Transform(P2, new_P2), Transform(P3, new_P3), Transform(bezier_line1, new_bezier_line1),
                  Transform(bezier_line2, new_bezier_line2), Transform(bezier_interpolation[0], new_bezier))

        self.wait(5)


class Scene_2_4(Scene):
    def construct(self):
        vertical_division = Line([0, 3, 0], [0, -3, 0], color=DARK_GREY)
        horizontal_division = Line([-6, 0, 0], [6, 0, 0], color=DARK_GREY)
        divisions = VGroup(vertical_division, horizontal_division)

        linear_bezier = Scene_2_4.create_bezier_quadrant([[-4, 1, 0], [-1, 2, 0]], color=YELLOW_D)
        quadratic_bezier = Scene_2_4.create_bezier_quadrant([[4, 1, 0], [2.5, 2, 0], [1, 1, 0]], color=BLUE_C)
        cubic_bezier = Scene_2_4.create_bezier_quadrant([[-3.5, -2.5, 0], [-4.5, -1, 0], [-2, -2, 0], [-1, -1.5, 0]])
        quartic_bezier = Scene_2_4.create_bezier_quadrant([[5, -1.5, 0], [4, -2.5, 0], [3, -1, 0], [1, -2, 0],
                                                           [2, -2.5, 0]], color=YELLOW_D)

        self.play(Create(divisions))
        self.play(Create(linear_bezier), Create(quadratic_bezier), Create(cubic_bezier), Create(quartic_bezier))

        quadratic_bezier[-2].generate_target()  # P2
        quadratic_bezier[-4].generate_target()  # curve
        quadratic_bezier[-5].generate_target()  # line 2
        quadratic_bezier[-6].generate_target()  # line 1
        quadratic_bezier[-2].target.shift(UP)
        bezier_points = [bezier_curve(t / 20, [quadratic_bezier[-3].get_center(),
                                               quadratic_bezier[-2].target.get_center(),
                                               quadratic_bezier[-1].get_center()]) + [0] for t in range(21)]
        quadratic_bezier[-4].target = VMobject().set_points_smoothly(bezier_points)
        quadratic_bezier[-5].target = Line(quadratic_bezier[-2].target.get_center(),
                                           quadratic_bezier[-1].get_center(), stroke_width=1, color=BLUE_C)
        quadratic_bezier[-6].target = Line(quadratic_bezier[-3].get_center(),
                                           quadratic_bezier[-2].target.get_center(), stroke_width=1, color=BLUE_C)

        self.play(MoveToTarget(quadratic_bezier[-2]), MoveToTarget(quadratic_bezier[-4]),
                  MoveToTarget(quadratic_bezier[-5]), MoveToTarget(quadratic_bezier[-6]))

        cubic_bezier[-3].generate_target()  # P2
        cubic_bezier[-5].generate_target()  # curve
        cubic_bezier[-7].generate_target()  # line 2
        cubic_bezier[-8].generate_target()  # line 1
        cubic_bezier[-3].target.shift(2 * RIGHT)
        bezier_points = [bezier_curve(t / 30, [cubic_bezier[-4].get_center(),
                                               cubic_bezier[-3].target.get_center(),
                                               cubic_bezier[-2].get_center(),
                                               cubic_bezier[-1].get_center()]) + [0] for t in range(31)]
        cubic_bezier[-5].target = VMobject().set_points_smoothly(bezier_points)
        cubic_bezier[-7].target = Line(cubic_bezier[-3].target.get_center(),
                                       cubic_bezier[-2].get_center(), stroke_width=1, color=BLUE_C)
        cubic_bezier[-8].target = Line(cubic_bezier[-4].get_center(),
                                       cubic_bezier[-3].target.get_center(), stroke_width=1, color=BLUE_C)

        self.play(MoveToTarget(cubic_bezier[-3]), MoveToTarget(cubic_bezier[-5]),
                  MoveToTarget(cubic_bezier[-7]), MoveToTarget(cubic_bezier[-8]))

        quartic_bezier[-3].generate_target()  # P3
        quartic_bezier[-6].generate_target()  # curve
        quartic_bezier[-8].generate_target()  # line 2
        quartic_bezier[-9].generate_target()  # line 1
        quartic_bezier[-3].target.shift(LEFT, 0.8 * UP)
        bezier_points = [bezier_curve(t / 40, [quartic_bezier[-5].get_center(),
                                               quartic_bezier[-4].get_center(),
                                               quartic_bezier[-3].target.get_center(),
                                               quartic_bezier[-2].get_center(),
                                               quartic_bezier[-1].get_center()]) + [0] for t in range(41)]
        quartic_bezier[-6].target = VMobject().set_points_smoothly(bezier_points)
        quartic_bezier[-8].target = Line(quartic_bezier[-3].target.get_center(),
                                         quartic_bezier[-2].get_center(), stroke_width=1, color=YELLOW_D)
        quartic_bezier[-9].target = Line(quartic_bezier[-4].get_center(),
                                         quartic_bezier[-3].target.get_center(), stroke_width=1, color=YELLOW_D)

        self.play(MoveToTarget(quartic_bezier[-3]), MoveToTarget(quartic_bezier[-6]),
                  MoveToTarget(quartic_bezier[-8]), MoveToTarget(quartic_bezier[-9]))

        self.wait(1)
        self.play(Uncreate(quadratic_bezier), Uncreate(cubic_bezier), Uncreate(quartic_bezier))
        self.wait(5)

    @staticmethod
    def create_bezier_quadrant(points, color=BLUE_C):
        bezier = VGroup()
        P = []

        for i, p in enumerate(points):
            dot = Dot(p, color=color)
            P.append(dot)

        for i, p in enumerate(points[:-1]):
            bezier.add(Line(p, points[i + 1], stroke_width=1, color=color))

        bezier_points = [bezier_curve(t / len(P * 10), [point.get_center() for point in P]) + [0]
                         for t in range(len(P) * 10 + 1)]
        bezier.add(VMobject().set_points_smoothly(bezier_points))

        for dot in P:
            bezier.add(dot)

        return bezier


class Scene_2_5(Scene):
    def construct(self):
        color1 = YELLOW_D
        color2 = BLUE_C
        color3 = GREEN_C
        color4 = PURPLE_C

        vertical_division = Line([0, 3, 0], [0, -3, 0], color=DARK_GREY)
        horizontal_division = Line([-6, 0, 0], [6, 0, 0], color=DARK_GREY)
        divisions = VGroup(vertical_division, horizontal_division)

        P1_dot = Dot([-4, 1, 0])
        P2_dot = Dot([-1, 2, 0])
        curve = Line(P1_dot.get_center(), P2_dot.get_center(), color=color1)

        P1_text = Text("P1", color=BLACK, size=0.25).move_to(P1_dot.get_center()).set_opacity(0)
        P2_text = Text("P2", color=BLACK, size=0.25).move_to(P2_dot.get_center()).set_opacity(0)
        dot_size = 0.2 + P1_text.get_width() / 2

        P1 = VGroup(P1_dot, P1_text)
        P2 = VGroup(P2_dot, P2_text)
        bezier_group = VGroup(curve, P1_dot, P2_dot, P1_text, P2_text)

        self.add(divisions, bezier_group, P1_text, P2_text)

        bezier_group.generate_target()
        bezier_group.target.scale(2)

        bezier_group.target.submobjects[-4] = Dot(radius=dot_size, color=color1)\
            .move_to(bezier_group.target[-2].get_center())
        bezier_group.target.submobjects[-3] = Dot(radius=dot_size, color=color1)\
            .move_to(bezier_group.target[-1].get_center())

        bezier_group.target[-2].move_to(bezier_group.target[-4].get_center()).set_opacity(1)
        bezier_group.target[-1].move_to(bezier_group.target[-3].get_center()).set_opacity(1)
        bezier_group.target[0].set_color(WHITE)

        bezier_group.target.move_to([0, 0, 0]).shift(LEFT)

        title_dot = Dot().next_to(bezier_group.target, UP).shift(5 * LEFT, 0.5 * UP)
        title_text = Text("Linear Bézier Curve", t2c={"Linear": color1}).next_to(title_dot, RIGHT)

        subtitle_text = Text("degree 1", size=0.6, t2c={"[6:]": color1}).next_to(title_dot, RIGHT)
        subtitle_text.shift(DOWN)

        info_dot = Dot().shift(2 * DOWN, LEFT)
        control_points_text = Text("2 control points", size=0.5, t2c={"2": color1}).next_to(info_dot, RIGHT)
        directions_text = Text("0 directional changes", size=0.5, t2c={"0": color1})\
            .next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        text_group = VGroup(title_text, subtitle_text, control_points_text, directions_text)
        text_group.generate_target()
        curve.generate_target()

        self.play(Uncreate(divisions), MoveToTarget(bezier_group), Write(text_group))
        self.wait(1)

        text_group.target.submobjects[0] = title_text = Text("Quadratic Bézier Curve", t2c={"Quadratic": color2})\
            .next_to(title_dot, RIGHT)
        text_group.target.submobjects[1] = Text("degree 2", size=0.6, t2c={"[6:]": color2}).next_to(title_dot, RIGHT)\
            .shift(DOWN)
        text_group.target.submobjects[2] = Text("3 control points", size=0.5, t2c={"3": color2})\
            .next_to(info_dot, RIGHT)
        text_group.target.submobjects[3] = Text("1 directional changes", size=0.5, t2c={"1": color2})\
            .next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        P3_dot = P2_dot.copy()
        P3_text = Text("P3", color=BLACK, size=0.5).move_to(P3_dot.get_center())
        P3 = VGroup(P3_dot, P3_text)
        self.bring_to_back(curve, P3)

        for P in (P1, P2, P3):
            P.generate_target()
            P.target[0].set_color(color2)
        
        P1.target.shift(0.5 * DOWN)
        P2.target.shift(3 * LEFT)
        P3.target.shift(DOWN)

        bezier_points = [bezier_curve(t / 20, [P1.target.get_center(),
                                               P2.target.get_center(),
                                               P3.target.get_center()]) + [0] for t in range(21)]
        curve.target = VMobject().set_points_smoothly(bezier_points)

        self.play(MoveToTarget(text_group), MoveToTarget(P1), MoveToTarget(P2), MoveToTarget(P3), MoveToTarget(curve))
        self.wait(1)

        text_group.target.submobjects[0] = title_text = Text("Cubic Bézier Curve", t2c={"Cubic": color3}) \
            .next_to(title_dot, RIGHT)
        text_group.target.submobjects[1] = Text("degree 3", size=0.6, t2c={"[6:]": color3}).next_to(title_dot, RIGHT) \
            .shift(DOWN)
        text_group.target.submobjects[2] = Text("4 control points", size=0.5, t2c={"4": color3})\
            .next_to(info_dot, RIGHT)
        text_group.target.submobjects[3] = Text("2 directional changes", size=0.5, t2c={"2": color3}) \
            .next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        P4_dot = P3_dot.copy()
        P4_text = Text("P4", color=BLACK, size=0.5).move_to(P4_dot.get_center())
        P4 = VGroup(P4_dot, P4_text)
        self.bring_to_back(curve, P4)

        for P in (P1, P2, P3, P4):
            P.generate_target()
            P.target[0].set_color(color3)

        P1.target.shift(0.5 * DOWN)
        P2.target.shift(LEFT, 0.5 * DOWN)
        P3.target.shift(0.5 * LEFT, DOWN)
        P4.target.shift(UP, 2 * LEFT)

        bezier_points = [bezier_curve(t / 30, [P1.target.get_center(),
                                               P2.target.get_center(),
                                               P3.target.get_center(),
                                               P4.target.get_center()]) + [0] for t in range(31)]
        curve.target = VMobject().set_points_smoothly(bezier_points)

        self.play(MoveToTarget(text_group), MoveToTarget(P1), MoveToTarget(P2), MoveToTarget(P3), MoveToTarget(P4),
                  MoveToTarget(curve))
        self.wait(1)

        text_group.target.submobjects[0] = title_text = Text("Quartic Bézier Curve", t2c={"Quartic": color4}) \
            .next_to(title_dot, RIGHT)
        text_group.target.submobjects[1] = Text("degree d = 4", size=0.6, t2c={"[6:]": color4},
                                                t2s={'d = 4': ITALIC}).next_to(title_dot, RIGHT).shift(DOWN)
        text_group.target.submobjects[2] = Text("d + 1 = 5 control points", size=0.5, t2c={"[0:5]": color4},
                                                t2s={'d + 1 = 5': ITALIC}).next_to(info_dot, RIGHT)
        text_group.target.submobjects[3] = Text("d - 1 = 3 directional changes", size=0.5, t2c={"[0:5]": color4},
                                                t2s={'d - 1 = 3': ITALIC}).next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        P5_dot = P4_dot.copy()
        P5_text = Text("P5", color=BLACK, size=0.5).move_to(P5_dot.get_center())
        P5 = VGroup(P5_dot, P5_text)
        self.bring_to_back(curve, P5)

        for P in (P1, P2, P3, P4, P5):
            P.generate_target()
            P.target[0].set_color(color4)

        P2.target.shift(DOWN, 4 * LEFT)
        P3.target.shift(3 * LEFT, 2 * UP)
        P4.target.shift(3 * RIGHT)
        P5.target.shift(2 * RIGHT, 2 * DOWN)

        bezier_points = [bezier_curve(t / 40, [P1.target.get_center(),
                                               P2.target.get_center(),
                                               P3.target.get_center(),
                                               P4.target.get_center(),
                                               P5.target.get_center()]) + [0] for t in range(41)]
        curve.target = VMobject().set_points_smoothly(bezier_points)

        self.play(MoveToTarget(text_group), MoveToTarget(P1), MoveToTarget(P2), MoveToTarget(P3), MoveToTarget(P4),
                  MoveToTarget(P5), MoveToTarget(curve))

        self.wait(5)


class Scene_2_6(Scene):
    def construct(self):
        color1 = YELLOW_D
        color2 = BLUE_C
        color3 = GREEN_C
        color4 = PURPLE_C

        P1_dot = Dot([-4, 1, 0])
        P2_dot = Dot([-1, 2, 0])
        curve = Line(P1_dot.get_center(), P2_dot.get_center(), color=color1)

        P1_text = Text("P1", color=BLACK, size=0.25).move_to(P1_dot.get_center()).set_opacity(0)
        P2_text = Text("P2", color=BLACK, size=0.25).move_to(P2_dot.get_center()).set_opacity(0)
        dot_size = 0.2 + P1_text.get_width() / 2

        P1 = VGroup(P1_dot, P1_text)
        P2 = VGroup(P2_dot, P2_text)
        bezier_group = VGroup(curve, P1_dot, P2_dot, P1_text, P2_text)

        self.add(bezier_group, P1_text, P2_text)

        bezier_group.generate_target()
        bezier_group.target.scale(2)

        bezier_group.target.submobjects[-4] = Dot(radius=dot_size, color=color1) \
            .move_to(bezier_group.target[-2].get_center())
        bezier_group.target.submobjects[-3] = Dot(radius=dot_size, color=color1) \
            .move_to(bezier_group.target[-1].get_center())

        bezier_group.target[-2].move_to(bezier_group.target[-4].get_center()).set_opacity(1)
        bezier_group.target[-1].move_to(bezier_group.target[-3].get_center()).set_opacity(1)
        bezier_group.target[0].set_color(WHITE)

        bezier_group.target.move_to([0, 0, 0]).shift(LEFT)

        title_dot = Dot().next_to(bezier_group.target, UP).shift(5 * LEFT, 0.5 * UP)
        title_text = Text("Linear Bézier Curve", t2c={"Linear": color1}).next_to(title_dot, RIGHT)

        subtitle_text = Text("degree d = 1", size=0.6, t2c={"[6:]": color1}).next_to(title_dot, RIGHT)
        subtitle_text.shift(DOWN)

        info_dot = Dot().shift(2 * DOWN, LEFT)
        control_points_text = Text("d + 1 = 2 control points", size=0.5, t2c={"[0:5]": color1},
                                   t2s={'d + 1 = 2': ITALIC}).next_to(info_dot, RIGHT)
        directions_text = Text("d - 1 = 0 directional changes", size=0.5, t2c={"[0:5]": color1},
                               t2s={'d - 1 = 0': ITALIC}).next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        text_group = VGroup(title_text, subtitle_text, control_points_text, directions_text)
        text_group.generate_target()
        curve.generate_target()

        self.play(MoveToTarget(bezier_group), Write(text_group))
        self.wait(1)

        text_group.target.submobjects[0] = title_text = Text("Quadratic Bézier Curve", t2c={"Quadratic": color2}) \
            .next_to(title_dot, RIGHT)
        text_group.target.submobjects[1] = Text("degree d = 2", size=0.6, t2c={"[6:]": color2}).next_to(title_dot, RIGHT) \
            .shift(DOWN)
        text_group.target.submobjects[2] = Text("d + 1 = 3 control points", size=0.5, t2c={"[0:5]": color2},
                                                t2s={'d + 1 = 3': ITALIC}).next_to(info_dot, RIGHT)
        text_group.target.submobjects[3] = Text("d - 1 = 1 directional changes", size=0.5, t2c={"[0:5]": color2},
                                                t2s={'d - 1 = 1': ITALIC}).next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        P3_dot = P2_dot.copy()
        P3_text = Text("P3", color=BLACK, size=0.5).move_to(P3_dot.get_center())
        P3 = VGroup(P3_dot, P3_text)
        self.bring_to_back(curve, P3)

        for P in (P1, P2, P3):
            P.generate_target()
            P.target[0].set_color(color2)

        P1.target.shift(0.5 * DOWN)
        P2.target.shift(3 * LEFT)
        P3.target.shift(DOWN)

        bezier_points = [bezier_curve(t / 20, [P1.target.get_center(),
                                               P2.target.get_center(),
                                               P3.target.get_center()]) + [0] for t in range(21)]
        curve.target = VMobject().set_points_smoothly(bezier_points)

        self.play(MoveToTarget(text_group), MoveToTarget(P1), MoveToTarget(P2), MoveToTarget(P3), MoveToTarget(curve))
        self.wait(1)

        text_group.target.submobjects[0] = title_text = Text("Cubic Bézier Curve", t2c={"Cubic": color3}) \
            .next_to(title_dot, RIGHT)
        text_group.target.submobjects[1] = Text("degree d = 3", size=0.6, t2c={"[6:]": color3}).next_to(title_dot, RIGHT) \
            .shift(DOWN)
        text_group.target.submobjects[2] = Text("d + 1 = 4 control points", size=0.5, t2c={"[0:5]": color3},
                                                t2s={'d + 1 = 4': ITALIC}).next_to(info_dot, RIGHT)
        text_group.target.submobjects[3] = Text("d - 1 = 2 directional changes", size=0.5, t2c={"[0:5]": color3},
                                                t2s={'d - 1 = 2': ITALIC}).next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        P4_dot = P3_dot.copy()
        P4_text = Text("P4", color=BLACK, size=0.5).move_to(P4_dot.get_center())
        P4 = VGroup(P4_dot, P4_text)
        self.bring_to_back(curve, P4)

        for P in (P1, P2, P3, P4):
            P.generate_target()
            P.target[0].set_color(color3)

        P1.target.shift(0.5 * DOWN)
        P2.target.shift(LEFT, 0.5 * DOWN)
        P3.target.shift(0.5 * LEFT, DOWN)
        P4.target.shift(UP, 2 * LEFT)

        bezier_points = [bezier_curve(t / 30, [P1.target.get_center(),
                                               P2.target.get_center(),
                                               P3.target.get_center(),
                                               P4.target.get_center()]) + [0] for t in range(31)]
        curve.target = VMobject().set_points_smoothly(bezier_points)

        self.play(MoveToTarget(text_group), MoveToTarget(P1), MoveToTarget(P2), MoveToTarget(P3), MoveToTarget(P4),
                  MoveToTarget(curve))
        self.wait(1)

        text_group.target.submobjects[0] = title_text = Text("Quartic Bézier Curve", t2c={"Quartic": color4}) \
            .next_to(title_dot, RIGHT)
        text_group.target.submobjects[1] = Text("degree d = 4", size=0.6, t2c={"[6:]": color4},
                                                t2s={'d = 4': ITALIC}).next_to(title_dot, RIGHT).shift(DOWN)
        text_group.target.submobjects[2] = Text("d + 1 = 5 control points", size=0.5, t2c={"[0:5]": color4},
                                                t2s={'d + 1 = 5': ITALIC}).next_to(info_dot, RIGHT)
        text_group.target.submobjects[3] = Text("d - 1 = 3 directional changes", size=0.5, t2c={"[0:5]": color4},
                                                t2s={'d - 1 = 3': ITALIC}).next_to(info_dot, RIGHT).shift(0.5 * DOWN)

        P5_dot = P4_dot.copy()
        P5_text = Text("P5", color=BLACK, size=0.5).move_to(P5_dot.get_center())
        P5 = VGroup(P5_dot, P5_text)
        self.bring_to_back(curve, P5)

        for P in (P1, P2, P3, P4, P5):
            P.generate_target()
            P.target[0].set_color(color4)

        P2.target.shift(DOWN, 4 * LEFT)
        P3.target.shift(3 * LEFT, 2 * UP)
        P4.target.shift(3 * RIGHT)
        P5.target.shift(2 * RIGHT, 2 * DOWN)

        bezier_points = [bezier_curve(t / 40, [P1.target.get_center(),
                                               P2.target.get_center(),
                                               P3.target.get_center(),
                                               P4.target.get_center(),
                                               P5.target.get_center()]) + [0] for t in range(41)]
        curve.target = VMobject().set_points_smoothly(bezier_points)

        self.play(MoveToTarget(text_group), MoveToTarget(P1), MoveToTarget(P2), MoveToTarget(P3), MoveToTarget(P4),
                  MoveToTarget(P5), MoveToTarget(curve))

        self.wait(5)


class Scene_3_1(Scene):
    def construct(self):
        question = Text("How do Bézier Curves work?", t2c={"[0:3]": RED_C})

        self.play(Write(question))

        self.wait(5)


if __name__ == '__main__':
    print(f'cd Documentation/YouTube/"BezierCurves #1"')
    print(f'manim video_scenes.py Scene_SCENE --preview --flush_cache -qh')
