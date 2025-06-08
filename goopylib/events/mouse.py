"""
goopylib module that deals with mouse buttons and events
"""

from __future__ import annotations

try:
    from typing import Final
except ImportError:
    from typing_extensions import Final

MOUSE_LEFT_BUTTON: Final[int] = 0
MOUSE_RIGHT_BUTTON: Final[int] = 1
MOUSE_MIDDLE_BUTTON: Final[int] = 2

MOUSE_BUTTON_4: Final[int] = 3
MOUSE_BUTTON_5: Final[int] = 4
MOUSE_BUTTON_6: Final[int] = 5
MOUSE_BUTTON_7: Final[int] = 6
MOUSE_BUTTON_8: Final[int] = 7
