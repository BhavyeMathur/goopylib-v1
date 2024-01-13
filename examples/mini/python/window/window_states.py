import goopylib as gp
import time

# Create a new window of size 500x500 pixels, then update it to show the window
window = gp.Window(500, 500, "Window States")
gp.update()
time.sleep(1)

# After 1 second, minimize the window
window.minimize()
gp.update()
time.sleep(1)

# After 1 second, restore the window to normal
window.restore()
gp.update()
time.sleep(1)

# After 1 second, maximize the window
window.maximize()
gp.update()
time.sleep(1)

# After 1 second, restore the window to normal
window.restore()
gp.update()
time.sleep(1)

# Terminate goopylib
gp.terminate()
