import goopylib as gp
import plot

ease = gp.ease_linear()
data = [ease(x / 100) for x in range(101)]

# Plotting the data
plot.lineplot("goopylib Linear Ease Function", data)

gp.terminate()
