import goopylib.imports as gp
import plot

# Plotting the Polynomial Ease Function
ease = gp.ease_poly()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Polynomial Ease Function", data)

# # Plotting the Polynomial Ease In Function
ease = gp.ease_poly_in()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Polynomial Ease In Function", data)
#
# # Plotting the Polynomial Ease Out Function
ease = gp.ease_poly_out()
data = [ease(x / 100) for x in range(101)]
plot.lineplot("goopylib Polynomial Ease Out Function", data)

gp.terminate()
