import matplotlib.pyplot as plt
import seaborn as sns
import math

sns.set_theme()


def plot_all_easing(easings):
    rows = math.ceil(len(easings) / 6)
    fig, axes = plt.subplots(nrows=rows, ncols=6, figsize=(36, 6 * rows), dpi=100)

    x_ax = [x / 100 for x in range(101)]

    for i, (name, ease) in enumerate(easings):
        axes[i // 6][i % 6].set_title(name.title(), fontdict={"size": 20, "weight": "bold"}, pad=20)
        axes[i // 6][i % 6].plot(x_ax, [ease(x) for x in x_ax])

    plt.tight_layout()

    fig.savefig(f"/Users/bhavyemathur/CLionProjects/goopylib/docs/_static/easing/all.png")
    plt.show()


def plot_easing_variants(name: str, ease, ease_in, ease_out):
    fig, axes = plt.subplots(ncols=3, figsize=(18, 6), dpi=100)

    x_ax = [x / 100 for x in range(101)]
    name = name.title()

    axes[0].set_title(f"{name} Ease In", fontdict={"size": 15, "weight": "bold"}, pad=15)
    axes[0].plot(x_ax, [ease_in(x) for x in x_ax])

    axes[1].set_title(f"{name} Ease Out", fontdict={"size": 15, "weight": "bold"}, pad=15)
    axes[1].plot(x_ax, [ease_out(x) for x in x_ax])

    axes[2].set_title(f"{name} Ease", fontdict={"size": 15, "weight": "bold"}, pad=15)
    axes[2].plot(x_ax, [ease(x) for x in x_ax])

    plt.tight_layout()

    fig.savefig(f"/Users/bhavyemathur/CLionProjects/goopylib/docs/_static/easing/{name.lower()}.png")


def plot_easing(name: str, ease):
    fig, axes = plt.subplots(figsize=(6, 6), dpi=100)

    x_ax = [x / 100 for x in range(101)]
    name = name.capitalize()

    axes.set_title(f"{name} Ease", fontdict={"size": 15, "weight": "bold"}, pad=15)
    axes.plot(x_ax, [ease(x) for x in x_ax])

    plt.tight_layout()

    fig.savefig(f"/Users/bhavyemathur/CLionProjects/goopylib/docs/_static/easing/{name.lower()}.png")
