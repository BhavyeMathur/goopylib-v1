import goopylib as gp


def maximize_callback(maximized):
    print(f"Window maximized? {maximized}")


def minimize_callback(minimized):
    print(f"Window minimized? {minimized}")


def focused_callback(focused):
    print(f"Window focused? {focused}")


def space_key_callback(action):
    print(f"Space key pressed? {action}")


def mouse_motion_callback(xpos, ypos):
    """Silenced because it clutters the console"""
    # print("Cursor moved to (%f, %f)", xpos, ypos)


def mouse_enter_callback(entered):
    print(f"Mouse entered window? {entered}")


def scroll_callback(xscroll, yscroll):
    print(f"Scroll changed to ({xscroll}, {yscroll})")


def left_click_callback(pressed):
    print(f"Left button clicked? {pressed}")


def middle_click_callback(pressed):
    print(f"Middle button clicked? {pressed}")


def right_click_callback(pressed):
    print(f"Right button clicked? {pressed}")


def main():
    window = gp.Window(500, 500, "Window Callback Functions")

    window.resizable = True
    window.set_size_limits(200, 200, 900, 900)

    window.resize_callback = lambda width, height: print(f"Resized window to size ({width}, {height})")
    window.close_callback = lambda: print("Closed window")
    window.destroy_callback = lambda: print("Destroyed window")

    window.maximize_callback = maximize_callback
    window.minimize_callback = minimize_callback
    window.focus_callback = focused_callback

    # window.set_key_callback(gp.KEY_SPACE, space_key_callback)

    window.mouse_motion_callback = mouse_motion_callback
    window.mouse_enter_callback = mouse_enter_callback
    window.scroll_callback = scroll_callback

    window.left_click_callback = left_click_callback
    # window.middle_click_callback = middle_click_callback
    # window.right_click_callback = right_click_callback

    while window.is_open():
        gp.update()

    gp.terminate()


if __name__ == "__main__":
    main()
