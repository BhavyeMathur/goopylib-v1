import goopylib as gp


window = gp.Window(500, 500, "Merry Christmas!")
window.background = "#1a1d24"

# Tree Leaves
for i in range(4):
    triangle = gp.Triangle((-100, -50), (100, -50), (0, 50)).draw(window)
    triangle.set_color("#AEDD70")
    triangle.y += 45 * i * (0.95 ** i)
    triangle.scale(0.8 ** i)


# Tree Trunk
triangle = gp.Triangle((-15, -50), (15, -50), (-15, -120)).draw(window)
triangle.set_color("#4d4036")

triangle = gp.Triangle((-15, -120), (15, -50), (15, -120)).draw(window)
triangle.set_color("#4d4036")


while window.is_open():
    gp.update_on_event()

gp.terminate()
