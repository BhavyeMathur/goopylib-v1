from goopylib.imports import *

window = GraphWin("Test Window", width=110, height=110, autoflush=False, bk_colour=WHITE)
e = Entry(Point(55, 55), text_width=10).draw(window)

create_custom_ease()

#Text(Point(55, 55), text=window.get_bk_colour(), font_colour=WHITE, font_size=12, font_style="bold").draw(window)
""""
while True:
    
    mouse_pos = window.check_left_mouse_click()
    if mouse_pos is not None:
        print(mouse_pos, e.get_width(), e.get_height())
    if e.is_clicked(mouse_pos):
        print(1)
    
    window.update_win()"""

"""
from tkinter.filedialog import askopenfilename
filename = askopenfilename()"""
