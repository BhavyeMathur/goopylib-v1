from goopylib.colours import *
from goopylib.util import GraphicsError

global_style = "default"

STYLES = {"pycharm darcula": {"primary fill": DARK_GREY, "secondary fill": BLUE_GREY, "background": DARK_GREY,
                              "primary outline": None, "secondary outline": DARK_BLUE_GREY, "accent": LIGHT_BLUE_GREY,

                              "width": 1,
                              "font colour": LIGHTER_GREY, "justify": "center", "font": "century gothic",
                              "font size": 20, "font style": "normal"},

          "intellij": {"primary fill": DARK_GREY, "secondary fill": DARK_WHITE, "background": WHITE,
                       "primary outline": None, "secondary outline": LIGHTER_GREY, "accent": LIGHT_BLUE_GREY,

                       "width": 1,
                       "text colour": LIGHTER_GREY, "justify": "left", "font": ("century gothic", 20, "normal")},

          "default": {"primary fill": CHROME_YELLOW, "secondary fill": RED, "fill": CHROME_YELLOW, "background": WHITE,
                      "primary outline": BLACK, "secondary outline": GREY, "outline": BLACK,

                      "width": "2", "arrow": "none", "entry width": 0,
                      "text colour": BLACK, "text": "Lorem Ipsum", "justify": "center",
                      "font": "calibri", "font_size": 5, "font style": "normal", "font colour": BLACK,
                      "select colour": BLUE},
          }


# Add other colour definitions here!

############################################################################
# Graphics classes start here

def set_style(style="default"):
    global global_style

    if style not in STYLES.keys():
        raise GraphicsError(f"The style specified ({style}) does not exist, must be one of {list(STYLES.keys())}")
    global_style = style
