import goopylib as gp

window = gp.Window(812, 812, "Batch Rendering Lines!")

N = 100
distance = 812 / N

lines = []

for i in range(N):
    pos = distance * i - 406

    lines.append(gp.Line((pos, -406), (pos, 406), 2))
    lines.append(gp.Line((-406, pos), (406, pos), 2))

for line in lines:
    line.draw(window)


while window.is_open():
    gp.update()

gp.terminate()
