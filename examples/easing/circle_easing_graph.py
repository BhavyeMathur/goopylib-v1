import goopylib as gp
import plot

# Plotting the Circle Ease Function
ease = gp.ease_circle()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Circle Ease Function", data)

# Plotting the Circle Ease In Function
ease = gp.ease_circle_in()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Circle Ease In Function", data)

# Plotting the Circle Ease Out Function
ease = gp.ease_circle_out()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Circle Ease Out Function", data)

gp.terminate()
