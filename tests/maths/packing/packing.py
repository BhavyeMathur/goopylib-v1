import random

import goopylib.imports as gp


def get_packing_algorithm():
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

        Enter Choice: """

    if (choice := input(choices)) == "":
        func = gp.packing.shelf.BestAreaFit
    else:
        func = [gp.packing.shelf.NextFit,
                gp.packing.shelf.FirstFit,
                gp.packing.shelf.BestWidthFit,
                gp.packing.shelf.WorstWidthFit,
                gp.packing.shelf.BestHeightFit,
                gp.packing.shelf.WorstHeightFit,
                gp.packing.shelf.BestAreaFit,
                gp.packing.shelf.WorstAreaFit,

                ][int(choice) - 1]

    return func


def create_random_items(n):
    return [gp.packing.Item(width=5 + 65 * random.random(),
                            height=5 + 75 * random.random()) for _ in range(n)]


def pack_items(items, packing, bin_size):
    algorithm = packing(*bin_size)
    algorithm.pack_all(items)
    return algorithm.bins()


def print_packing_ratio(bins):
    packing_ratio = 0
    for i, bin in enumerate(bins):
        packing_ratio += bin.packing_ratio()
        print(f"Packing Ratio for Bin {i}: {round(100 * bin.packing_ratio(), 3)}%")

    print(f"Average Packing Ratio: {round(100 * packing_ratio / len(bins), 3)}%")


def plot_item_bins(bins, window_size):
    window = gp.Window(window_size[0], window_size[1], "Rectangle Packing Algorithms using goopylib!")
    window.get_camera().set_projection(0, window_size[0], 0, window_size[1])

    colors = [gp.Color(65, 110, 230), gp.Color(190, 240, 140), gp.Color(80, 60, 160),
              gp.Color(220, 120, 140), gp.Color(120, 220, 250)]

    def show_page(p):
        for k, objs in enumerate(objects):
            for rect in objs:
                rect.hide(k != p)

    def get_object_color(k):
        return colors[k % len(colors)]

    objects = []
    for i, bin in enumerate(bins):
        objects.append([])

        for j, item in enumerate(bin.items()):
            obj = gp.Rectangle(item.p1(), item.p2())
            obj.set_color(get_object_color(j))
            obj.draw(window)

            objects[-1].append(obj)

    page = 0
    show_page(0)

    while window.is_open():
        if window.check_key(gp.KEY_LEFT) or window.check_key(gp.KEY_RIGHT):
            page += -1 if window.check_key(gp.KEY_LEFT) else 1
            page %= len(bins)
            show_page(page)

            while window.check_key(gp.KEY_LEFT) or window.check_key(gp.KEY_RIGHT):
                gp.update()

        gp.update()


def main(packing, window_size=(800, 800)):
    print("Algorithm:", packing.__name__, end="\n\n")

    random.seed(0)
    items = create_random_items(500)

    bins = pack_items(items, packing, window_size)
    print_packing_ratio(bins)

    plot_item_bins(bins, window_size)


if __name__ == "__main__":
    main(packing=get_packing_algorithm())

gp.terminate()
