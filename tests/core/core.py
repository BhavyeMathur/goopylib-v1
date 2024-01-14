import goopylib as gp


gp.init()

print("Refresh Rate:", gp.get_refresh_rate())
print("Screen Width:", gp.get_screen_width())
print("Screen Height:", gp.get_screen_height())
print("# of Monitors:", gp.number_of_monitors())
print()
print("GLFW Compiled Version:", gp.glfw_compiled_version())
print("GLFW Current Version:", gp.glfw_current_version())

# goopylib provides 3 update functions
gp.update()

# These have been commented out because without an active window, they will simply pause the program
# gp.update_on_event()
# gp.update_timeout(60)

# edit the default update rate to update at 30 FPS
gp.set_buffer_swap_interval(30)

gp.terminate()
