"""
goopylib module that deals with keyboard keys and events
"""

from typing import Final

KEY_UNKNOWN: Final[int] = -1

KEY_SPACE: Final[int] = 32
KEY_APOSTROPHE: Final[int] = 39  # '
KEY_COMMA: Final[int] = 44  # ,
KEY_MINUS: Final[int] = 45  # -
KEY_PERIOD: Final[int] = 46  # .
KEY_SLASH: Final[int] = 47  # /

KEY_0: Final[int] = 48
KEY_1: Final[int] = 49
KEY_2: Final[int] = 50
KEY_3: Final[int] = 51
KEY_4: Final[int] = 52
KEY_5: Final[int] = 53
KEY_6: Final[int] = 54
KEY_7: Final[int] = 55
KEY_8: Final[int] = 56
KEY_9: Final[int] = 57

KEY_SEMICOLON: Final[int] = 59  # ;
KEY_EQUAL: Final[int] = 61  # =

KEY_A: Final[int] = 65
KEY_B: Final[int] = 66
KEY_C: Final[int] = 67
KEY_D: Final[int] = 68
KEY_E: Final[int] = 69
KEY_F: Final[int] = 70
KEY_G: Final[int] = 71
KEY_H: Final[int] = 72
KEY_I: Final[int] = 73
KEY_J: Final[int] = 74
KEY_K: Final[int] = 75
KEY_L: Final[int] = 76
KEY_M: Final[int] = 77
KEY_N: Final[int] = 78
KEY_O: Final[int] = 79
KEY_P: Final[int] = 80
KEY_Q: Final[int] = 81
KEY_R: Final[int] = 82
KEY_S: Final[int] = 83
KEY_T: Final[int] = 84
KEY_U: Final[int] = 85
KEY_V: Final[int] = 86
KEY_W: Final[int] = 87
KEY_X: Final[int] = 88
KEY_Y: Final[int] = 89
KEY_Z: Final[int] = 90

KEY_LEFT_BRACKET: Final[int] = 91  # [
KEY_RIGHT_BRACKET: Final[int] = 93  # ]
KEY_BACKSLASH: Final[int] = 92  # \
KEY_GRAVE_ACCENT: Final[int] = 96  # ~

KEY_WORLD_1: Final[int] = 161
KEY_WORLD_2: Final[int] = 162

KEY_ESCAPE: Final[int] = 256
KEY_ENTER: Final[int] = 257
KEY_TAB: Final[int] = 258
KEY_BACKSPACE: Final[int] = 259
KEY_INSERT: Final[int] = 260
KEY_DELETE: Final[int] = 261

KEY_RIGHT: Final[int] = 262
KEY_LEFT: Final[int] = 263
KEY_DOWN: Final[int] = 264
KEY_UP: Final[int] = 265

KEY_PAGE_UP: Final[int] = 266
KEY_PAGE_DOWN: Final[int] = 267

KEY_HOME: Final[int] = 268
KEY_END: Final[int] = 269

KEY_CAPS_LOCK: Final[int] = 280
KEY_SCROLL_LOCK: Final[int] = 281
KEY_NUM_LOCK: Final[int] = 282
KEY_PRINT_SCREEN: Final[int] = 283
KEY_PAUSE: Final[int] = 284

KEY_F1: Final[int] = 290
KEY_F2: Final[int] = 291
KEY_F3: Final[int] = 292
KEY_F4: Final[int] = 293
KEY_F5: Final[int] = 294
KEY_F6: Final[int] = 295
KEY_F7: Final[int] = 296
KEY_F8: Final[int] = 297
KEY_F9: Final[int] = 298
KEY_F10: Final[int] = 299
KEY_F11: Final[int] = 300
KEY_F12: Final[int] = 301
KEY_F13: Final[int] = 302
KEY_F14: Final[int] = 303
KEY_F15: Final[int] = 304
KEY_F16: Final[int] = 305
KEY_F17: Final[int] = 306
KEY_F18: Final[int] = 307
KEY_F19: Final[int] = 308
KEY_F20: Final[int] = 309
KEY_F21: Final[int] = 310
KEY_F22: Final[int] = 311
KEY_F23: Final[int] = 312
KEY_F24: Final[int] = 313
KEY_F25: Final[int] = 314

KEY_KP_0: Final[int] = 320
KEY_KP_1: Final[int] = 321
KEY_KP_2: Final[int] = 322
KEY_KP_3: Final[int] = 323
KEY_KP_4: Final[int] = 324
KEY_KP_5: Final[int] = 325
KEY_KP_6: Final[int] = 326
KEY_KP_7: Final[int] = 327
KEY_KP_8: Final[int] = 328
KEY_KP_9: Final[int] = 329

KEY_KP_DECIMAL: Final[int] = 330
KEY_KP_DIVIDE: Final[int] = 331
KEY_KP_MULTIPLY: Final[int] = 332
KEY_KP_SUBTRACT: Final[int] = 333
KEY_KP_ADD: Final[int] = 334
KEY_KP_ENTER: Final[int] = 335
KEY_KP_EQUAL: Final[int] = 336

KEY_LEFT_SHIFT: Final[int] = 340
KEY_LEFT_CONTROL: Final[int] = 341
KEY_LEFT_ALT: Final[int] = 342
KEY_LEFT_SUPER: Final[int] = 343

KEY_RIGHT_SHIFT: Final[int] = 344
KEY_RIGHT_CONTROL: Final[int] = 345
KEY_RIGHT_ALT: Final[int] = 346
KEY_RIGHT_SUPER: Final[int] = 347

KEY_MENU: Final[int] = 348
