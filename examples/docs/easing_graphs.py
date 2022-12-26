import math

import matplotlib.pyplot as plt
import seaborn as sns

import goopylib.imports as gp

sns.set_theme()


def plot_all_easing(easings):
    rows = math.ceil(len(easings) / 6)
    fig, axes = plt.subplots(nrows=rows, ncols=6, figsize=(36, 6 * rows), dpi=100)

    x_ax = [x / 100 for x in range(101)]

    for i, (name, ease) in enumerate(easings):
        axes[i // 6][i % 6].set_title(name.title(), fontdict={"size": 20, "weight": "bold"}, pad=20)
        axes[i // 6][i % 6].plot(x_ax, [ease(x) for x in x_ax])

    plt.tight_layout()

    fig.savefig(f"../../docs/_static/easing/all.png")
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

    fig.savefig(f"../../docs/_static/easing/{name.lower()}.png")


def plot_easing(name: str, ease):
    fig, axes = plt.subplots(figsize=(6, 6), dpi=100)

    x_ax = [x / 100 for x in range(101)]
    name = name.capitalize()

    axes.set_title(f"{name} Ease", fontdict={"size": 15, "weight": "bold"}, pad=15)
    axes.plot(x_ax, [ease(x) for x in x_ax])

    plt.tight_layout()

    fig.savefig(f"../../docs/_static/easing/{name.lower()}.png")


plot_easing("Combined", gp.combine_easing(gp.ease_elastic_in(), gp.ease_bounce_out()))

plot_all_easing([("Polynomial In", gp.ease_poly_in()), ("Polynomial Out", gp.ease_poly_out()),
                 ("Polynomial", gp.ease_poly()),
                 ("Quadratic In", gp.ease_quad_in()), ("Quadratic Out", gp.ease_quad_out()),
                 ("Quadratic", gp.ease_quad()),
                 ("Cubic In", gp.ease_cubic_in()), ("Cubic Out", gp.ease_cubic_out()),
                 ("Cubic", gp.ease_cubic()),
                 ("Quartic In", gp.ease_quart_in()), ("Quartic Out", gp.ease_quart_out()),
                 ("Quartic", gp.ease_quart()),
                 ("Quintic In", gp.ease_quint_in()), ("Quintic Out", gp.ease_quint_out()),
                 ("Quintic", gp.ease_quint()),
                 ("Sine In", gp.ease_sin_in()), ("Sine Out", gp.ease_sin_out()),
                 ("Sine", gp.ease_sin()),
                 ("Exponential In", gp.ease_exp_in()), ("Exponential Out", gp.ease_exp_out()),
                 ("Exponential", gp.ease_exp()),
                 ("Circle In", gp.ease_circle_in()), ("Circle Out", gp.ease_circle_out()),
                 ("Circle", gp.ease_circle()),
                 ("Back In", gp.ease_back_in()), ("Back Out", gp.ease_back_out()),
                 ("Back", gp.ease_back()),
                 ("Elastic In", gp.ease_elastic_in()), ("Elastic Out", gp.ease_elastic_out()),
                 ("Elastic", gp.ease_elastic()),
                 ("Bounce In", gp.ease_bounce_in()), ("Bounce Out", gp.ease_bounce_out()),
                 ("Bounce", gp.ease_bounce()),
                 ("Linear", gp.ease_linear())])

plot_easing("Linear", gp.ease_linear())

plot_easing_variants("Polynomial", gp.ease_poly(), gp.ease_poly_in(), gp.ease_poly_out())
plot_easing_variants("Quadratic", gp.ease_quad(), gp.ease_quad_in(), gp.ease_quad_out())
plot_easing_variants("Cubic", gp.ease_cubic(), gp.ease_cubic_in(), gp.ease_cubic_out())
plot_easing_variants("Quartic", gp.ease_quart(), gp.ease_quart_in(), gp.ease_quart_out())
plot_easing_variants("Quintic", gp.ease_quint(), gp.ease_quint_in(), gp.ease_quint_out())

plot_easing_variants("Sine", gp.ease_sin(), gp.ease_sin_in(), gp.ease_sin_out())
plot_easing_variants("Exponential", gp.ease_exp(), gp.ease_exp_in(), gp.ease_exp_out())
plot_easing_variants("Circle", gp.ease_circle(), gp.ease_circle_in(), gp.ease_circle_out())

plot_easing_variants("Back", gp.ease_back(), gp.ease_back_in(), gp.ease_back_out())
plot_easing_variants("Elastic", gp.ease_elastic(), gp.ease_elastic_in(), gp.ease_elastic_out())
plot_easing_variants("Bounce", gp.ease_bounce(), gp.ease_bounce_in(), gp.ease_bounce_out())

gp.terminate()
