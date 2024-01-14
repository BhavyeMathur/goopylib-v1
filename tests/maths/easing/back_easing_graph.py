import goopylib.imports as gp
import plot

# Plotting the Back Ease Function
ease = gp.ease_back()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Back Ease Function", data)

# Plotting the Back Ease In Function
ease = gp.ease_back_in()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Back Ease In Function", data)

# Plotting the Back Ease Out Function
ease = gp.ease_back_out()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Back Ease Out Function", data)

gp.terminate()
