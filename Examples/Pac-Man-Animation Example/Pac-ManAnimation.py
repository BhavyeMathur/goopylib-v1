from goopylib.imports import *

# Creating a window with the given title, width, height and background colour
window = GraphWin(title="Simple Pac-Man Animation", width=600, height=200, bk_colour=DARKEST_NAVY_BLUE)

# We can reference PacMan using the 'PacMan' string now as it is tagged with it
pacman_frames = [f"PacMan{frame}.png" for frame in range(6)]
objects = [AnimatedImage(Point(220, 100), pacman_frames, tag="PacMan").draw()]

for index, ghost in enumerate(("Blinky", "Pinky", "Inky", "Clyde")):
    x = 300 + (index * 50)
    ghost_frames = [f"{ghost}{frame}.png" for frame in range(6)]

    # The position to the draw the Animated Image & the texture file to use, then pasting the pupils of the ghost on top
    objects.append(AnimatedImage(Point(x, 100), ghost_frames)  # Binding the frame keeps it synchronized with other Animated Images
                   .alpha_composite(Image(Point(x, 100), "Pupils.png")).draw().bind_frame_to("PacMan"))

last_update = time.time()  # The time module is automatically imported
while True:
    if time.time() - last_update > 0.03333:  # Moving the graphics every 1/30 seconds
        last_update = time.time()

        for obj in objects:
            obj.move_x(-5)
            if obj.get_x_pos() < 0:  # Checks if the object has exited the screen
                obj.move_to_x(600)  # Takes it back to the other side is True

    window.update_win()  # Updating the window
