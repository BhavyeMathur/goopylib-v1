from cProfile import Profile
from pstats import SortKey, Stats
import pstats

import goopylib.imports as gp
from goopylib.layout import *

SCREEN_WIDTH = 900
SCREEN_HEIGHT = 600

with Div(860, 600, classes="screen") as screen:
    with Div(width="50%", height="560px", margin=20, padding=10, classes="col1",
             flex=Flex("wrap", "space-between", "start", "centre")):

        with Div(width="120px", height="auto", padding=10, classes="col11",
                 flex=Flex("reverse", align="centre", cross_align="space-around", item_align="centre",
                           direction="column", row_gap=5, column_gap=0)):

            for i in range(5):
                with Div(width="100%", height="auto" if i % 2 else "30px", margin=5,
                         min_width="50%", min_height="10px", max_height="60px", classes="test",
                         flex=Flex("wrap", align="centre", direction="row-reverse", grow=0.1 if i % 2 else 1)):

                    for i in range(20):
                        Div(width="5px", height="5px", classes="mini-square")

        Div(width="25%", height="50%", classes="box")
        Div(width="25%", height="50%", classes="box")
        Div(width="25%", height="50%", classes="box")
        Div(width="25%", height="50%", classes="box")

    Div(width="20%", height="100%", classes="col2")

pstats.f8 = lambda x: "%14.6f" % x
with Profile() as profile:
    for _ in range(50):
        process(screen, x=-SCREEN_WIDTH // 2, y=-SCREEN_HEIGHT // 2)
    Stats(profile).strip_dirs().sort_stats(SortKey.CALLS).print_stats()

window = gp.Window(SCREEN_WIDTH, SCREEN_HEIGHT, title="goopylib's new Layout Engine!")


def draw(rectangle):
    rectangle.y *= -1
    rectangle.draw(window)


margin_colour = gp.Color("#e8435f")
border_colour = gp.Color("#000")
padding_colours = [gp.Color("#eee"), gp.Color("#7db5fa")]
content_colours = [gp.Color("#fff"), gp.Color("#5a9ced")]

for container in Div.get_instances():
    margin = gp.Rectangle(container.margin_box.start, container.margin_box.end)
    margin.set_color(margin_colour)
    draw(margin)

    padding_start = container.padding_box.start
    padding_end = container.padding_box.end
    content_start = container.padding_box.start
    content_end = container.padding_box.end

    border = gp.Rectangle(padding_start, padding_end)
    border.set_color(border_colour)
    draw(border)

    padding = gp.Rectangle((padding_start[0] + 1, padding_start[1] + 1), (padding_end[0] - 1, padding_end[1] - 1))
    padding.set_color(padding_colours[container.layer % len(padding_colours)])
    draw(padding)

    rect = gp.Rectangle((content_start[0] + 1, content_start[1] + 1), (content_end[0] - 1, content_end[1] - 1))
    rect.set_color(content_colours[container.layer % len(content_colours)])
    draw(rect)

while window.is_open():
    gp.update()

gp.terminate()
