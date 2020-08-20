from goopylib.colours import *
from goopylib.util import GraphicsError

global_style = "default"

STYLES = {"default": {"fill": CHROME_YELLOW, "background": WHITE,
                      "outline": BLACK, "line outline": GREY, "width": 2,

                      # Config for the Line Class
                      "line width": 3, "capstyle": "round", "joinstyle": "round", "arrow": "none",
                      "arrowshape": (8, 10, 3), "dash": None,

                      # Config for the Entry class
                      "entry width": 0, "select colour": BLUE,

                      # Config for Font & Text
                      "text": "Lorem Ipsum", "justify": "center", "font face": "calibri",
                      "font size": 10, "font style": "normal", "font colour": BLACK},
          }


# Add other colour definitions here!

############################################################################
# Graphics classes start here

def set_style(style="default"):
    global global_style

    if style not in STYLES.keys():
        raise GraphicsError(f"The style specified ({style}) does not exist, must be one of {list(STYLES.keys())}")
    global_style = style
