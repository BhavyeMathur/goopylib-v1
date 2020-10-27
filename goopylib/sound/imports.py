try:
    from goopylib.sound.Sound import *
    from goopylib.sound.waves import *
except ImportError as e:
    print(f"The sound package has not been imported due to an error: {e}")
