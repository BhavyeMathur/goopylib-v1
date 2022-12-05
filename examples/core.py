import goopylib as gp


gp.init()

print("Refresh Rate:", gp.get_refresh_rate())
print("Screen Width:", gp.get_screen_width())
print("Screen Height:", gp.get_screen_height())
print("# of Monitors:", gp.number_of_monitors())
print()
print("GLFW Compiled Version:", gp.glfw_compiled_version())
print("GLFW Current Version:", gp.glfw_current_version())

gp.terminate()
