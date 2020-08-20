from goopylib.imports import *

# Creating a window with the given title, width, height and background colour
window = GraphWin(title="Simple Pac-Man Animation", width=600, height=200, bk_colour=DARKEST_NAVY_BLUE)

# We can reference PacMan using the 'PacMan' string now as it is tagged with it
# The Point() defines where to create the Animated Image
# The List argument defines what frames (img paths) to use for the aniamted image
# The movement bounds define the boundaries the object can move in - in this, it is a rectangle the size of the window
# The True after the rectangle means that the object returns to the other side of the rectangle once it crosses an edge
objects = [AnimatedImage(Point(220, 100), [f"PacMan{frame}.png" for frame in range(5)], tag="PacMan",
                         update_time=1/15).set_movement_bounds(Rectangle(Point(0, 0), Point(600, 200)), True).draw()]

for index, ghost in enumerate(("Blinky", "Pinky", "Inky", "Clyde")):
    # The position to the draw the Animated Image & the texture file to use, then pasting the pupils of the ghost on top
    # Binding the frame keeps it synchronized with other Animated Images
    # We copy the movement bounds of the object from the object tagged "PacMan"
    objects.append(AnimatedImage(Point(300 + (index * 50), 100), [f"{ghost}{frame}.png" for frame in range(6)],
                                 update_time=1/15).copy_movement_bounds_from("PacMan")
                   .alpha_composite(Image(Point(300 + (index * 50), 100), "Pupils.png")).bind_frame_to("PacMan").draw())

while True:
    for obj in objects:
        obj.move_x(-4)

    window.update_win()  # Updating the window
    update(30)  # Updating the window at a rate of 30 FPS
