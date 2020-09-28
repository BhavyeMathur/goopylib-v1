from goopylib.imports import *

window = Window(title="Hello World!", width=500, height=500, bk_colour=DARKEST_GREY)  # Creating the window

Rectangle([0, 220], [500, 280], fill=DARK_GREY, outline_width=0).draw()  # Drawing a rectangle in the back

# Creates the title text and makes it glide in from the side with an elastic ease for 2 seconds
title = Text([0, 250], "Hello World!", text_align="center", font_colour=WHITE, font_size=30,
             font_face="Century Gothic", font_style="bold").draw()
title.glide_to_x(250, time=2, easing=py_ease_elastic_out())

# Creates the subtitle and makes it glide in from the bottom with a circle ease for 2 seconds
subtitle = Text([250, 520], "Bhavye's 2nd program", text_align="center", font_colour=WHITE, font_size=12,
                font_face="Century Gothic").draw()
subtitle.glide(0, 0, time=1)
subtitle.glide_to_y(300, time=2, easing=py_ease_circle_out())

while True:  # The Mainloop
    window.update()  # Updating the Window
