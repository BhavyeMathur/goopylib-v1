from goopylib.imports import *

def create_custom_ease():
    window = GraphWin(title="goopylib: Create Custom Ease", width=get_screen_size()[1] * 0.7,
                      height=get_screen_size()[1] * 0.7, autoflush=False, bk_colour=DARKER_GREY)
    window.set_coords(0, 0, 1000, 1000)

    while True:
        window.update_win()

