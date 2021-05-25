from goopylib.imports import *

# Creating a window with the given title, width, height and background colour
window = Window(title="Simple Pac-Man Animation", width=600, height=200, bk_colour=DARKEST_NAVY_BLUE)

# We can reference PacMan using the 'PacMan' string now as it is tagged with it
# The Point() defines where to create the Animated Image
# The List argument defines what frames (img paths) to use for the animated image
# The movement bounds define the boundaries the object can move in - in this, it is the window
# The True after the window means that the object returns to the other side of the window once it crosses its edge
objects = [AnimatedImage([220, 100], [f"PacMan{frame}.png" for frame in range(5)], tag="PacMan",
                         update_time=1/15).set_movement_bounds(window, True).draw()]

for index, ghost in enumerate(("Blinky", "Pinky", "Inky", "Clyde")):
    # The Animated Image parameters are the position to the draw the Animated Image & the texture file to use
    # Binding the frame keeps it synchronized with other Animated Images
    objects.append(AnimatedImage([300 + (index * 50), 100], [f"{ghost}{frame}.png" for frame in range(6)],
                                 update_time=1/15).bind_frame_to("PacMan").draw())
    # The alpha composite pastes the pupils of the ghost on top of every frame in the Animated Image
    # The get_anchor() function returns the position of an object.
    # This draws the pupils in the same position as the ghost
    # We copy the movement bounds of the object from the object tagged "PacMan"
    objects[-1].copy_movement_bounds_from("PacMan").alpha_composite(Image(objects[-1].get_anchor(), "Pupils.png"))

while True:  # This is the main loop
    for obj in objects:
        obj.move_x(-4)  # Moving each object left by 4 pixels

    window.update()  # Updating the window
    update(24)  # Updating the loop at a rate of 30 FPS
