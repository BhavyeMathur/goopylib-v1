from goopylib.colours import *
from goopylib.util import GraphicsError

global_style = "default"

STYLES = {"default": {"fill": CHROME_YELLOW, "background": WHITE,
                      "outline": BLACK, "line outline": GREY,

                      "width": 2, "line width": 3, "arrow": "none", "entry width": 0,
                      "text colour": BLACK, "text": "Lorem Ipsum", "justify": "center",
                      "font face": "calibri", "font size": 10, "font style": "normal", "font colour": BLACK,
                      "select colour": BLUE, "font": (10, "calibri", "normal")},
          }


# Add other colour definitions here!

############################################################################
# Graphics classes start here

def set_style(style="default"):
    global global_style

    if style not in STYLES.keys():
        raise GraphicsError(f"The style specified ({style}) does not exist, must be one of {list(STYLES.keys())}")
    global_style = style
