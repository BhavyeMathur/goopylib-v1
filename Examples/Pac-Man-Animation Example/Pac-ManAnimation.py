from goopy import *

class Object:
    def __init__(self, ghostNumber, name):
        self.animationFrame = 0
        self.name = name

        self.xPos = 300 + ghostNumber * 50 if self.name != "PacMan" else 250  # Get the intial X position

        # Here, we draw the graphics of the object (pacman or the ghosts)
        # The graphics are organized as '{name}{frame}.png' where increasing the frame animates the object

        if self.name != "PacMan":
            self.graphic = Image(Point(self.xPos, 100), f"{self.name}{self.animationFrame}.png") \
                .alphaComposite(Image(Point(self.xPos, 100), f"Pupils.png")).draw(window) # Compositing basically pastes an image on top of another
                # Here, we are compositing the pupils of the Ghost
        else:
            self.graphic = Image(Point(self.xPos, 100), f"{self.name}{self.animationFrame}.png").draw(window)

    def update(self):
        # Increase the current animation frame.
        self.animationFrame += 0.5  # We increase by 0.5 because we want to slow down the animation and take the int(animationFrame) later
        self.xPos -= 3  # Change the xPosition

        self.graphic.undraw()  # Undraw the graphic to draw it again with a new frame

        # Here, we take the modulus of the xPos because we want the objects to return from the other side of the window
        # We take the modulus of the animationFrame because we have only 6 frames per object
        if self.name != "PacMan":
            self.graphic = Image(Point(self.xPos % 600, 100), f"{self.name}{int(self.animationFrame) % 6}.png")\
                .alphaComposite(Image(Point(self.xPos % 600, 100), f"Pupils.png")).draw(window)
        else:
            self.graphic = Image(Point(self.xPos % 600, 100), f"{self.name}{int(self.animationFrame) % 6}.png").draw(window)


# Creating a window. The autoflush parameter controls whether the window automatically updates, in this case, it doesn't
# We are also setting the dimensions of the window to be relative to the screen size to cope with different screens
# with different resolutions.
window = GraphWin(title="Simple Pac-Man Animation", width=getScreenSize()[1]*0.5, height=getScreenSize()[1]*0.5 * 0.33,
                  autoflush=False, bkColour=DARKEST_NAVY_BLUE)
window.setCoords(0, 0, 600, 200)  # Setting the coordinates of the window from top-left to bottom-right

# Creating the 4 ghosts & Pac-Man
objects = [Object(index, name) for index, name in enumerate(["PacMan", "Blinky", "Pinky", "Inky", "Clyde"])]

while True:
    for obj in objects:  # Updating the ghosts & Pac-Man to make them move & animate
        obj.update()
    window.updateWin()  # Updating the window
    update(24)  # Updating this loop at a rate of 24 FPS
