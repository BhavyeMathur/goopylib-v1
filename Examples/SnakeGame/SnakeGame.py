from goopylib.imports import *  # imports everything (* means everything) from goopylib
import random

# Makes a square window with title as 'Snake Game', and width and height of 600
window = Window(title="Snake Game", width=600, height=600, icon="WindowIcon.ico")

# Alternates values between 0 and 1 and colours the rectangles in the grid according to its value
# if colour_value is 0, then the rectangle is light
# if colour_value is 1, then the rectangle is dark
colour_value = 0

for x in range(20):  # for each square on the x axis, do the y for loop
    # there are 21 squares on the y-axis to make it an even number, the 21st layer of squares is hidden
    # because it is outside the window
    for y in range(21):  # for each square on the y axis, do whatever is inside this for loop

        # Scale the value of x and y (which go from 0-19) by 30 so that they go from 0-570
        x_pos = x * 30  # the size of each square is 30 pixels
        y_pos = y * 30  # multiplying the x and y value by 30 gives us the start position of each square

        # 0 -> 0
        # 1 -> 30
        # 2 -> 60
        # ...

        # If colour_value is 0, the square is light
        # If colour_value is 1, the square is dark

        # The square_colour variable is used to keep a track of which colour the rectangle is

        # flips the value of colour_value between 0 & 1 so that a square of an alternating colour is created each time
        if colour_value == 0:  # if colour_value is 0, flip the value to 1
            colour_value = 1
            square_colour = DARK_NAVY_BLUE

        elif colour_value == 1:  # if colour_value is 1, flip the value to 0
            colour_value = 0
            square_colour = DARKER_NAVY_BLUE

        # Makes the rectangles at the x_pos and y_pos which square_colour as the colour and no outline
        Rectangle([x_pos, y_pos], [x_pos + 30, y_pos + 30], fill=square_colour, outline_width=0).draw(window)

# ----------------------------------------------------------------------------------------------------------------------
# Title & Subtitle Part

title = Text([300, 100], "SNAKE GAME", font_colour=WHITE, font_size=40, font_face="courier new", font_style="bold").draw(window)
subtitle = Text([300, 150], "Click to Start", font_colour=WHITE, font_size=15, font_face="courier new", font_style="bold").draw(window)

window.get_left_mouse_click()  # waits until the user clicks the window

title.destroy()

subtitle.glide_y(-100, time=0.5, easing=py_ease_sin_out)
subtitle.set_text("Score: 0")
score = 0

snake_directions = ["0", "0", "0"]  # List of the directions of each block in the snake, the head has a direction 'right'

# right right 0
# right right right

snake_squares = [Rectangle([150, 300], [180, 330], fill=LIGHTISH_BLUE, outline_width=0, layer=1).draw(window),
                 Rectangle([150, 300], [180, 330], fill=LIGHTISH_BLUE, outline_width=0, layer=1).draw(window),
                 Rectangle([150, 300], [180, 330], fill=LIGHTISH_BLUE, outline_width=0, layer=1).draw(window)]

# [x, y]
apple_position = [random.randint(0, 19) * 30 + 15, random.randint(0, 19) * 30 + 15]
# between [0, 0] and [19, 19]
apple = Circle(apple_position, 10, fill=LIGHTISH_RED).draw(window)
apple.animate_blinking(0.2)  # blinks the apple at a rate of 0.2 seconds

apple_eaten = False

# the mainloop
while window.is_open():
    window.update()
    update(6)  # runs the loop at a rate of 4 frames per second (FPS)

    # WASD and Left, Down, Right, Up

    key_pressed = window.check_key_press()

    snake_directions.pop()  # removes the last value in the list

    new_dir = snake_directions[0]  # sets the default value of new_dir to the direction of the head
    if (key_pressed == "Right" or key_pressed == "d") and new_dir != "left":
        new_dir = "right"
    elif (key_pressed == "Left" or key_pressed == "a") and new_dir != "right":
        new_dir = "left"
    elif (key_pressed == "Up" or key_pressed == "w") and new_dir != "down":
        new_dir = "up"
    elif (key_pressed == "Down" or key_pressed == "s") and new_dir != "up":
        new_dir = "down"

    snake_directions.insert(0, new_dir)

    position = snake_squares[0].get_anchor()  # get_anchor() returns the position of an object
    # position = [x, y]

    if position == apple_position:  # checks if the snake position is equal to the apple position
        apple_position = [random.randint(0, 19) * 30 + 15, random.randint(0, 19) * 30 + 15]  # gets a new apple position
        apple.move_to_point(apple_position)  # moves the apple to the new position

        score = score + 1  # increments the score by 1 every time the snake eats an apple
        subtitle.set_text(f"Score: {score}")

        snake_directions.append("0")  # adds an extra 0 direction to the end of the list
        new_square = Rectangle([150, 300], [180, 330], fill=LIGHTISH_BLUE, outline_width=0, layer=1).draw(window)
        new_square.move_to_point(snake_squares[-1].get_anchor())
        snake_squares.append(new_square)  # adds a copy of the tail square to the snake_square list

        apple_eaten = True

    # len(...) gives the length of the list
    for x in range(0, len(snake_squares)):  # x goes 0, then 1, then 2, etc.

        if snake_directions[x] == "right":
            snake_squares[x].move_x(30)

        elif snake_directions[x] == "left":
            snake_squares[x].move_x(-30)

        elif snake_directions[x] == "up":
            snake_squares[x].move_y(-30)

        elif snake_directions[x] == "down":
            snake_squares[x].move_y(30)

    touching_self = False
    if apple_eaten:
        #  list slicing [1:] -> returns all the values from the list from the first index to the last
        for square in snake_squares[1:]:  # goes through each square in the snake except the head
            if square.get_anchor() == position:  # checks if the head's position is the same as the other square
                touching_self = True

    # position[0] is the x value and position[1] is the y value
    if touching_self or (position[0] < 0) or (position[1] < 0) or (position[0] > 600) or (position[1] > 600):

        # the snake has hit the boundary, it dies

        # destroys the snake
        for square in snake_squares:  # go through each value in snake_squares, and call the variable 'square'
            square.destroy()  # remove the square
            window.update()  # update the window so that it can remove the square
            time.sleep(0.1)  # wait for 0.1 seconds

        # score and game over text

        title = Text([300, -100], "GAME OVER", font_colour=WHITE, font_size=40, font_face="courier new", font_style="bold").draw(window)
        subtitle.glide_y(100, time=0.5, easing=py_ease_sin_out)
        title.glide_y(200, time=0.5, easing=py_ease_sin_out)

        apple.destroy()

        while window.is_open():
            window.update()
