import random

import goopylib.imports as gp


def plot_packing(packing, window_size=(800, 800)):
    items = [gp.packing.Item(width=5 + 65 * random.random(),
                             height=5 + 75 * random.random()) for _ in range(500)]
    bins = packing(items, *window_size)

    window = gp.Window(window_size[0], window_size[1], "Rectangle Packing Algorithms using goopylib!")

    objects = []

    colors = [gp.Color(65, 110, 230), gp.Color(190, 240, 140), gp.Color(80, 60, 160),
              gp.Color(220, 120, 140), gp.Color(120, 220, 250)]

    packing_ratio = 0
    for i, bin in enumerate(bins):
        objects.append([])

        for j, item in enumerate(bin.items()):
            obj = gp.Rectangle(item.p1(), item.p2())
            obj.set_color(colors[j % len(colors)])
            obj.move(-window.width / 2, -window.height / 2)

            if i != 0:
                obj.hide()

            obj.draw(window)
            objects[-1].append(obj)

        packing_ratio += bin.packing_ratio()
        print(f"Packing Ratio for Bin {i}: {round(100 * bin.packing_ratio(), 3)}%")
    print(f"Average Packing Ratio: {round(100 * packing_ratio / len(bins), 3)}%")

    page = 0
    while window.is_open():
        if window.check_key(gp.KEY_LEFT) or window.check_key(gp.KEY_RIGHT):
            page += -1 if window.check_key(gp.KEY_LEFT) else 1
            page %= len(bins)

            for i, bin in enumerate(objects):
                for obj in bin:
                    obj.hide(i != page)

            while window.check_key(gp.KEY_LEFT) or window.check_key(gp.KEY_RIGHT):
                gp.update()

        gp.update()


choices = """
Choose an algorithm:
     ⏎ default
        
    Shelf Algorithms
    ----------------
        
     1. Shelf Next-Fit
     2. Shelf First-Fit
        
     3. Shelf Best Width Fit
     4. Shelf Worst Width Fit
        
     5. Shelf Best Height Fit
     6. Shelf Worst Height Fit
        
     7. Shelf Best Area Fit
     8. Shelf Worst Area Fit
        
    Oriented Shelf Algorithms
    -------------------------
        
     9. Oriented Shelf Next-Fit
    10. Oriented Shelf First-Fit
        
    11. Oriented Shelf Best Width Fit
    12. Oriented Shelf Worst Width Fit
        
    13. Oriented Shelf Best Height Fit
    14. Oriented Shelf Worst Height Fit
        
    15. Oriented Shelf Best Area Fit
    16. Oriented Shelf Worst Area Fit

Enter Choice: """

if (choice := input(choices)) == "":
    func = gp.packing.shelf.pack_best_area_fit
else:
    func = [gp.packing.shelf.pack_next_fit,
            gp.packing.shelf.pack_first_fit,
            gp.packing.shelf.pack_best_width_fit,
            gp.packing.shelf.pack_worst_width_fit,
            gp.packing.shelf.pack_best_height_fit,
            gp.packing.shelf.pack_worst_height_fit,
            gp.packing.shelf.pack_best_area_fit,
            gp.packing.shelf.pack_worst_area_fit,

            gp.packing.shelf.pack_oriented_next_fit,
            gp.packing.shelf.pack_oriented_first_fit,
            gp.packing.shelf.pack_oriented_best_width_fit,
            gp.packing.shelf.pack_oriented_worst_width_fit,
            gp.packing.shelf.pack_oriented_best_height_fit,
            gp.packing.shelf.pack_oriented_worst_height_fit,
            gp.packing.shelf.pack_oriented_best_area_fit,
            gp.packing.shelf.pack_oriented_worst_area_fit,
            ][int(choice) - 1]

print("Algorithm: ", func.__name__.replace("_", " ").title(), end="\n\n")
random.seed(0)
plot_packing(packing=func)

gp.terminate()
