import goopylib as gp
import plot

# Plotting the Sine Ease Function
ease = gp.ease_sin()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Sine Ease Function", data)

# Plotting the Sine Ease In Function
ease = gp.ease_sin_in()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Sine Ease In Function", data)

# Plotting the Sine Ease Out Function
ease = gp.ease_sin_out()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Sine Ease Out Function", data)

gp.terminate()
