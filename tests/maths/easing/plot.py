import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme()


def lineplot(title, data):
    plt.subplots(figsize=(8, 8), dpi=100)

    plt.title(title, fontdict={"size": 15, "weight": "bold"}, pad=20)
    plt.plot([x / 100 for x in range(101)], data)

    plt.show()
