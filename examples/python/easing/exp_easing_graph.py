import goopylib as gp
import plot

# Plotting the Exponential Ease Function
ease = gp.ease_exp()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Exponential Ease Function", data)

# Plotting the Exponential Ease In Function
ease = gp.ease_exp_in()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Exponential Ease In Function", data)

# Plotting the Exponential Ease Out Function
ease = gp.ease_exp_out()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Exponential Ease Out Function", data)

gp.terminate()
