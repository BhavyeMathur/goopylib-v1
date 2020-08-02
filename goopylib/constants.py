from tkinter import Tk as tkTk
from time import time as timetime

from PIL.Image import LANCZOS, BOX, BICUBIC, BILINEAR, NEAREST, HAMMING

import platform

# platform.system() gives Linux for Linux, Windows for Windows, and Darwin for MacOS
# https://stackoverflow.com/questions/1854/what-os-am-i-running-on
OS = platform.system()

# For the list of cursors visit:
CURSORS_RAW = {"x_cursor", "arrow", "based_arrow_down", "based_arrow_up", "boat", "bogosity", "bottom_left_corner",
               "bottom_right_corner", "bottom_side", "bottom_tee", "box_spiral", "center_ptr", "circle", "clock",
               "coffee_mug", "cross", "cross_reverse", "crosshair", "diamond_cross", "dot", "dotbox", "double_arrow",
               "draft_large", "draft_small", "draped_box", "exchange", "fleur", "gobbler", "gumby", "hand1", "hand2",
               "heart", "icon", "iron_cross", "left_ptr", "left_side", "left_tee", "leftbutton", "ll_angle", "lr_angle",
               "man", "middlebutton", "mouse", "pencil", "pirate", "plus", "question_arrow", "right_ptr", "right_side",
               "right_tee", "rightbutton", "rtl_logo", "sailboat", "sb_down_arrow", "sb_h_double_arrow",
               "sb_left_arrow", "sb_right_arrow", "sb_up_arrow", "sb_v_double_arrow", "shuttle", "sizing", "spider",
               "spraycan", "star", "target", "tcross", "top_left_arrow", "top_left_corner", "top_right_corner",
               "top_side", "top_tee", "trek", "ul_angle", "umbrella", "ur_angle", "watch", "xterm"}

CURSORS_WINDOWS_RAW = {"no", "starting", "size", "size_ne_sw", "size_ns", "size_nw_se", "size_we", "uparrow", "wait"}
CURSORS_MACOSX_RAW = {"copyarrow", "aliasarrow", "contextualmenuarrow", "text", "cross-hair", "closedhand", "openhand",
                      "pointinghand", "resizeleft", "resizeright", "resizeleftright", "resizeup", "resizedown",
                      "resizeupdown", "none", "notallowed", "poof", "countinguphand", "countingdownhand",
                      "countingupanddownhand", "spinning"}

CURSORS = {"x": "x_cursor", "arrow": "arrow", "based-down-arrow": "based_arrow_down",
           "based-up-arrow": "based_arrow_up", "boat": "boat", "maze_symbol": "bogosity",
           "bottom-left-corner-arrow": "bottom_left_corner", "bottom-right-corner-arrow": "bottom_right_corner",
           "download": "bottom_side", "bottom-t": "bottom_tee", "spiral": "box_spiral", "up-arrow-thin": "center_ptr",
           "donut": "circle", "clock": "clock", "mug": "coffee_mug", "double-plus": "cross",
           "inverted-plus": "cross_reverse", "crosshair": "crosshair", "diamond-plus": "diamond_cross", "circle": "dot",
           "box": "dotbox", "double-arrow": "double_arrow", "flipped-arrow": "draft_large",
           "thin-flipped-arrow": "draft_small", "diamond-box": "draped_box", "rotating-arrows": "exchange",
           "move": "fleur", "bird": "gobbler", "stickman": "gumby", "pointer": "hand1", "select": "hand2",
           "heart": "heart", "blackbox": "icon", "iron-cross": "iron_cross", "small-arrow": "left_ptr",
           "left-download": "left_side", "left-t": "left_tee", "left-button": "leftbutton",
           "bottom-left-corner": "ll_angle", "bottom-right-corner": "lr_angle", "volcano": "man",
           "middle-button": "middlebutton", "mouse": "mouse", "pencil": "pencil", "pirate": "pirate", "plus": "plus",
           "question-arrow": "question_arrow", "pointer-arrow": "right_ptr", "right-download": "right_side",
           "right-t": "right_tee", "right-button": "rightbutton", "maze": "rtl_logo", "sailboat": "sailboat",
           "down-arrow": "sb_down_arrow", "horizontal-resizing-arrow": "sb_h_double_arrow",
           "left-arrow": "sb_left_arrow", "right-arrow": "sb_right_arrow", "up-arrow": "sb_up_arrow",
           "vertical-resizing-arrow": "sb_v_double_arrow", "shuttle": "shuttle", "sizing": "sizing", "spider": "spider",
           "spraycan": "spraycan", "star": "star", "target": "target", "t-cross": "tcross",
           "flipped-pointer": "top_left_arrow", "top-left-corner-arrow": "top_left_corner",
           "top-right-corner-arrow": "top_right_corner", "top-download": "top_side", "top-t": "top_tee",
           "virus": "trek",
           "top-left-corner": "ul_angle", "umbrella": "umbrella", "top-right-corner": "ur_angle", "loading": "watch",
           "text-cursor": "xterm"}
CURSORS_WINDOWS = {"cancel": "no"}
CURSORS_MACOSX = {}

RELIEF = {"flat", "sunken", "raised", "groove", "ridge"}
ARROWS = {"both", "none", "first", "last"}

CAPSTYLES = {"round", "butt", "projecting"}
JOINSTYLES = {"bevel", "round", "miter"}
DASHES = {"solid": None, "dash": (5, ), "long dash": (8, ), "dot": (1, 3), "dashdot": (5, 1, 1, 1),
          "long dashdot": (8, 1, 1, 1)}

DUPLICATES_METRICS = {"Colour Animation": {"Change", "Start", "Time", "Update", "Initial", "Easing", "Final"},
                      "2D Animation": {"Change", "Start", "Time", "Update", "Initial", "EasingX", "EasingY", "Final"},
                      "1D Animation": {"Change", "Start", "Time", "Update", "Initial", "Easing", "Final"}}

CURVE_INTERPOLATIONS = {"linear", "cosine", "cubic", "hermite", "spline"}
IMAGE_INTERPOLATIONS = {"bicubic": BICUBIC, "bilinear": BILINEAR, "box": BOX, "nearest": NEAREST, "hamming": HAMMING,
                        "lanczos": LANCZOS}

ARC_TYPES = {"arc", "pieslice", "chord"}

ALIGN_OPTIONS = {"top", "left", "right", "bottom", "center", "topleft", "topright", "bottomleft", "bottomright"}

INTERPOLATIONS = {"linear", "poly", "poly_in", "poly_out", "sin", "sin_in", "sin_out", "circle", "circle_in",
                  "circle_out", "back", "back_in", "back_out", "bounce", "bounce_in", "bounce_out", "elastic",
                  "elastic_in", "elastic_out", "exponential", "exponential_in", "exponential_out"}

ALL_CHARACTERS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
                  'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                  'Y', 'Z', '!', '"', '#', '$', '%', '&', '\\', "'", '(', ')', '*', '+', ',', '-', '.', '/', ':', ';',
                  '<', '=', '>', '?', '@', '{', '\'', '"', '}', '^', '_', '`', '{', '|', '}', '~', ':', " "}

##########################################################################
# global variables and functions

_root = tkTk()
_root.withdraw()

_update_lasttime = timetime()
