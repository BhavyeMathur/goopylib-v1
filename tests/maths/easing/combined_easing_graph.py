import goopylib.imports as gp
import plot

# Plotting the Combined Ease Function
ease = gp.combine_easing(gp.ease_elastic_in(), gp.ease_bounce_out())
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Elastic-Bounce Ease Function", data)

gp.terminate()
