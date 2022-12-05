import goopylib as gp
import plot

# Plotting the Elastic Ease Function
ease = gp.ease_elastic()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Elastic Ease Function", data)

# Plotting the Elastic Ease In Function
ease = gp.ease_elastic_in()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Elastic Ease In Function", data)

# Plotting the Elastic Ease Out Function
ease = gp.ease_elastic_out()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Elastic Ease Out Function", data)

gp.terminate()
