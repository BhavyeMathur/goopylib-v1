from goopylib.colours import *
from goopylib.util import GraphicsError

global_style = "default"

STYLES = {"pycharm darcula": {"primary fill": DARK_GREY, "secondary fill": BLUE_GREY, "background": DARK_GREY,
                              "primary font_colour": None, "secondary font_colour": DARK_BLUE_GREY, "accent": LIGHT_BLUE_GREY,

                              "width": 1,
                              "font_face colour": LIGHTER_GREY, "justify": "center", "font_face": "century gothic",
                              "font_face size": 20, "font_face style": "normal"},

          "intellij": {"primary fill": DARK_GREY, "secondary fill": DARK_WHITE, "background": WHITE,
                       "primary font_colour": None, "secondary font_colour": LIGHTER_GREY, "accent": LIGHT_BLUE_GREY,

                       "width": 1,
                       "text colour": LIGHTER_GREY, "justify": "left", "font_face": ("century gothic", 20, "normal")},

          "default": {"primary fill": CHROME_YELLOW, "secondary fill": RED, "fill": CHROME_YELLOW, "background": WHITE,
                      "primary outline": BLACK, "secondary outline": GREY, "outline": BLACK,

                      "width": "2", "arrow": "none", "entry width": 0,
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
