import goopylib as gp
import plot

# Plotting the Bounce Ease Function
ease = gp.ease_bounce(bounces=3, damping=0.3)
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Bounce Ease Out Function", data)

# Plotting the Bounce Ease In Function
ease = gp.ease_bounce_in(bounces=8, damping=0.7)
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Bounce Ease In Function", data)

# Plotting the Bounce Ease Out Function
ease = gp.ease_bounce_out(bounces=5, damping=0.5)
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Bounce Ease Out Function", data)

gp.terminate()
