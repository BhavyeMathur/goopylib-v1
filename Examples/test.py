import timeit
import math
import os

from matplotlib import pyplot as plt

from goopylib.imports import *
import goopylib as gp

def countlines(start, lines=0, header=True, begin_start=None):
    if header:
        print('{:>10} |{:>10} | {:<20}'.format('ADDED', 'TOTAL', 'FILE'))
        print('{:->11}|{:->11}|{:->20}'.format('', '', ''))

    for thing in os.listdir(start):
        thing = os.path.join(start, thing)
        if os.path.isfile(thing):
            if thing.endswith('.py') or thing.endswith('.c') or thing.endswith('.h'):
                with open(thing, 'r') as f:
                    newlines = f.readlines()
                    newlines = len(newlines)
                    lines += newlines

                    if begin_start is not None:
                        reldir_of_thing = '.' + thing.replace(begin_start, '')
                    else:
                        reldir_of_thing = '.' + thing.replace(start, '')

                    print('{:>10} |{:>10} | {:<20}'.format(
                            newlines, lines, reldir_of_thing))

    for thing in os.listdir(start):
        thing = os.path.join(start, thing)
        if os.path.isdir(thing):
            lines = countlines(thing, lines, header=False, begin_start=start)

    return lines


def get_subclass_methods(cls):
    methods = set(dir(cls()))
    unique_methods = methods.difference(*(dir(base()) for base in cls.__bases__))
    return len(unique_methods)


def test_functions(functions_dict):
    max_test_string = max(len(", ".join(arg.__repr__() for arg in function["args"])
                              if isinstance(function["args"], (tuple, list)) else
                              ", ".join(f"{arg}={function['args'][arg].__repr__()}" for arg in function["args"]))
                          + len(function["func"].__name__) + 3
                          for function in functions_dict if isinstance(function, dict))

    print(f"{'{'}:^{max_test_string}{'}'}|\t{'{'}:^20{'}'}|\t{'{'}:^20{'}'}| {'{'}:^10{'}'}"
          .format("Function", "Actual Value", "Expected Value", "Status"))
    print(f"{'{'}:-<{max_test_string}{'}'}|{'{'}:-<21{'}'}|{'{'}:-<23{'}'}|{'{'}:-<10{'}'}".format('', '', '', ''))

    passed = 0
    total = 0
    for function in functions_dict:
        if function is None:
            print(f"{'{'}:<{max_test_string}{'}'}|{'{'}:<21{'}'}|{'{'}:<23{'}'}|{'{'}:<10{'}'}".format('', '', '', ''))
        else:
            if isinstance(function, str):
                print(f"\n{function}\n")
            else:
                args_string = ", ".join(arg.__repr__() for arg in function["args"])
                if isinstance(function["args"], (tuple, list)):
                    value = str(function["func"](*function["args"]))
                else:
                    value = str(function["func"](**function["args"]))
                    args_string = ", ".join(f"{arg}={function['args'][arg].__repr__()}" for arg in function["args"])

                expected = str(function["expected"])
                passed += value == expected

                if len(expected) > 20:
                    expected = expected[:17] + "..."
                if len(value) > 20:
                    value = value[:17] + "..."

                print(f"{'{'}:<{max_test_string}{'}'}|\t{'{'}:<20{'}'}|\t{'{'}:<20{'}'}| {'{'}{'}'}"
                      .format(f'{function["func"].__name__}({args_string})', value, expected,
                              '◼ Passed' if value == expected else '◻ Failed'))

                total += 1

    print(f"{'{'}:<{max_test_string}{'}'}|{'{'}:<21{'}'}|{'{'}:<23{'}'}|{'{'}:<10{'}'}".format('', '', '', ''))
    print(f"{'{'}:^{max_test_string}{'}'}|\t{'{'}:^20{'}'}|\t{'{'}:^20{'}'}| {'{'}{'}'}"
          .format("Total", f"{total} Tested", "-", f"{100 * passed/total}% Passed"))

def test_rgb_converter_functions(_test_function=True):
    functions_dict = [{"func": rgb_to_hex, "args": (255, 100, 40), "expected": "#ff6428"},
                      {"func": rgb_to_cmyk, "args": (255, 100, 40), "expected": (0, 61, 84, 0)},
                      {"func": rgb_to_hsl, "args": (255, 100, 40), "expected": (17, 100, 58)},
                      {"func": rgb_to_hsv, "args": (255, 100, 40), "expected": (17, 84, 100)},

                      {"func": rgb_to_hex, "args": (50, 250, 85), "expected": "#32fa55"},
                      {"func": rgb_to_cmyk, "args": (50, 250, 85), "expected": (80, 0, 66, 2)},
                      {"func": rgb_to_hsl, "args": (50, 250, 85), "expected": (130, 95, 59)},
                      {"func": rgb_to_hsv, "args": (50, 250, 85), "expected": (130, 80, 98)},

                      {"func": rgb_to_hex, "args": (105, 65, 245), "expected": "#6941f5"},
                      {"func": rgb_to_cmyk, "args": (105, 65, 245), "expected": (57, 73, 0, 4)},
                      {"func": rgb_to_hsl, "args": (105, 65, 245), "expected": (253, 90, 61)},
                      {"func": rgb_to_hsv, "args": (105, 65, 245), "expected": (253, 73, 96)},

                      #

                      {"func": gp.colours._rgb_to_hex, "args": (255, 100, 40), "expected": "#ff6428"},
                      {"func": gp.colours._rgb_to_cmyk, "args": (255, 100, 40), "expected": (0, 61, 84, 0)},
                      {"func": gp.colours._rgb_to_hsl, "args": (255, 100, 40), "expected": (17, 100, 58)},
                      {"func": gp.colours._rgb_to_hsv, "args": (255, 100, 40), "expected": (17, 84, 100)},

                      {"func": gp.colours._rgb_to_hex, "args": (50, 250, 85), "expected": "#32fa55"},
                      {"func": gp.colours._rgb_to_cmyk, "args": (50, 250, 85), "expected": (80, 0, 66, 2)},
                      {"func": gp.colours._rgb_to_hsl, "args": (50, 250, 85), "expected": (130, 95, 59)},
                      {"func": gp.colours._rgb_to_hsv, "args": (50, 250, 85), "expected": (130, 80, 98)},

                      {"func": gp.colours._rgb_to_hex, "args": (105, 65, 245), "expected": "#6941f5"},
                      {"func": gp.colours._rgb_to_cmyk, "args": (105, 65, 245), "expected": (57, 73, 0, 4)},
                      {"func": gp.colours._rgb_to_hsl, "args": (105, 65, 245), "expected": (253, 90, 61)},
                      {"func": gp.colours._rgb_to_hsv, "args": (105, 65, 245), "expected": (253, 73, 96)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict

def test_hex_converter_functions(_test_function=True):
    functions_dict = [{"func": hex_to_rgb, "args": ("#ff6428",), "expected": (255, 100, 40)},
                      {"func": hex_to_cmyk, "args": ("#ff6428",), "expected": (0, 61, 84, 0)},
                      {"func": hex_to_hsl, "args": ("#ff6428",), "expected": (17, 100, 58)},
                      {"func": hex_to_hsv, "args": ("#ff6428",), "expected": (17, 84, 100)},

                      {"func": gp.colours._hex_to_rgb, "args": ("#ff6428",), "expected": (255, 100, 40)},
                      {"func": gp.colours._hex_to_cmyk, "args": ("#ff6428",), "expected": (0, 61, 84, 0)},
                      {"func": gp.colours._hex_to_hsl, "args": ("#ff6428",), "expected": (17, 100, 58)},
                      {"func": gp.colours._hex_to_hsv, "args": ("#ff6428",), "expected": (17, 84, 100)}]
    if _test_function:
        test_functions(functions_dict)
    return functions_dict

def test_cmyk_converter_functions(_test_function=True):
    functions_dict = [{"func": cmyk_to_rgb, "args": (0, 61, 84, 0), "expected": (255, 99, 41)},
                      {"func": cmyk_to_hex, "args": (0, 61, 84, 0), "expected": "#ff6329"},
                      {"func": cmyk_to_hsl, "args": (0, 61, 84, 0), "expected": (16, 100, 58)},
                      {"func": cmyk_to_hsv, "args": (0, 61, 84, 0), "expected": (16, 84, 100)},

                      {"func": cmyk_to_rgb, "args": (64, 0, 10, 25), "expected": (69, 191, 172)},
                      {"func": cmyk_to_hex, "args": (64, 0, 10, 25), "expected": "#45bfac"},
                      {"func": cmyk_to_hsl, "args": (64, 0, 10, 25), "expected": (171, 49, 51)},
                      {"func": cmyk_to_hsv, "args": (64, 0, 10, 25), "expected": (171, 64, 75)},

                      {"func": cmyk_to_rgb, "args": (12, 17, 0, 55), "expected": (101, 95, 115)},
                      {"func": cmyk_to_hex, "args": (12, 17, 0, 55), "expected": "#655f73"},
                      {"func": cmyk_to_hsl, "args": (12, 17, 0, 55), "expected": (258, 9, 41)},
                      {"func": cmyk_to_hsv, "args": (12, 17, 0, 55), "expected": (258, 17, 45)},

                      {"func": cmyk_to_rgb, "args": (87, 79, 0, 74), "expected": (9, 14, 66)},
                      {"func": cmyk_to_hex, "args": (87, 79, 0, 74), "expected": "#090e42"},
                      {"func": cmyk_to_hsl, "args": (87, 79, 0, 74), "expected": (234, 77, 15)},
                      {"func": cmyk_to_hsv, "args": (87, 79, 0, 74), "expected": (234, 87, 26)},

                      #

                      {"func": gp.colours._cmyk_to_rgb, "args": (0, 61, 84, 0), "expected": (255, 99, 41)},
                      {"func": gp.colours._cmyk_to_hex, "args": (0, 61, 84, 0), "expected": "#ff6329"},
                      {"func": gp.colours._cmyk_to_hsl, "args": (0, 61, 84, 0), "expected": (16, 100, 58)},
                      {"func": gp.colours._cmyk_to_hsv, "args": (0, 61, 84, 0), "expected": (16, 84, 100)},

                      {"func": gp.colours._cmyk_to_rgb, "args": (64, 0, 10, 25), "expected": (69, 191, 172)},
                      {"func": gp.colours._cmyk_to_hex, "args": (64, 0, 10, 25), "expected": "#45bfac"},
                      {"func": gp.colours._cmyk_to_hsl, "args": (64, 0, 10, 25), "expected": (171, 49, 51)},
                      {"func": gp.colours._cmyk_to_hsv, "args": (64, 0, 10, 25), "expected": (171, 64, 75)},

                      {"func": gp.colours._cmyk_to_rgb, "args": (12, 17, 0, 55), "expected": (101, 95, 115)},
                      {"func": gp.colours._cmyk_to_hex, "args": (12, 17, 0, 55), "expected": "#655f73"},
                      {"func": gp.colours._cmyk_to_hsl, "args": (12, 17, 0, 55), "expected": (258, 9, 41)},
                      {"func": gp.colours._cmyk_to_hsv, "args": (12, 17, 0, 55), "expected": (258, 17, 45)},

                      {"func": gp.colours._cmyk_to_rgb, "args": (87, 79, 0, 74), "expected": (9, 14, 66)},
                      {"func": gp.colours._cmyk_to_hex, "args": (87, 79, 0, 74), "expected": "#090e42"},
                      {"func": gp.colours._cmyk_to_hsl, "args": (87, 79, 0, 74), "expected": (234, 77, 15)},
                      {"func": gp.colours._cmyk_to_hsv, "args": (87, 79, 0, 74), "expected": (234, 87, 26)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict

def test_hsv_converter_functions(_test_function=True):
    functions_dict = [{"func": hsv_to_rgb, "args": (16, 84, 100), "expected": (255, 98, 41)},
                      {"func": hsv_to_hex, "args": (16, 84, 100), "expected": "#ff6229"},
                      {"func": hsv_to_cmyk, "args": (16, 84, 100), "expected": (0, 62, 84, 0)},
                      {"func": hsv_to_hsl, "args": (16, 84, 100), "expected": (16, 100, 58)},

                      {"func": hsv_to_rgb, "args": (66, 32, 76), "expected": (188, 194, 132)},
                      {"func": hsv_to_hex, "args": (66, 32, 76), "expected": "#bcc284"},
                      {"func": hsv_to_cmyk, "args": (66, 32, 76), "expected": (3, 0, 32, 24)},
                      {"func": hsv_to_hsl, "args": (66, 32, 76), "expected": (66, 34, 64)},

                      {"func": hsv_to_rgb, "args": (179, 54, 48), "expected": (56, 122, 121)},
                      {"func": hsv_to_hex, "args": (179, 54, 48), "expected": "#387a79"},
                      {"func": hsv_to_cmyk, "args": (179, 54, 48), "expected": (54, 0, 1, 52)},
                      {"func": hsv_to_hsl, "args": (179, 54, 48), "expected": (179, 37, 35)},

                      {"func": hsv_to_rgb, "args": (302, 4, 11), "expected": (28, 27, 28)},
                      {"func": hsv_to_hex, "args": (302, 4, 11), "expected": "#1c1b1c"},
                      {"func": hsv_to_cmyk, "args": (302, 4, 11), "expected": (0, 4, 0, 89)},
                      {"func": hsv_to_hsl, "args": (302, 4, 11), "expected": (302, 2, 11)},

                      #

                      {"func": gp.colours._hsv_to_rgb, "args": (16, 84, 100), "expected": (255, 98, 41)},
                      {"func": gp.colours._hsv_to_hex, "args": (16, 84, 100), "expected": "#ff6229"},
                      {"func": gp.colours._hsv_to_cmyk, "args": (16, 84, 100), "expected": (0, 62, 84, 0)},
                      {"func": gp.colours._hsv_to_hsl, "args": (16, 84, 100), "expected": (16, 100, 58)},

                      {"func": gp.colours._hsv_to_rgb, "args": (66, 32, 76), "expected": (188, 194, 132)},
                      {"func": gp.colours._hsv_to_hex, "args": (66, 32, 76), "expected": "#bcc284"},
                      {"func": gp.colours._hsv_to_cmyk, "args": (66, 32, 76), "expected": (3, 0, 32, 24)},
                      {"func": gp.colours._hsv_to_hsl, "args": (66, 32, 76), "expected": (66, 34, 64)},

                      {"func": gp.colours._hsv_to_rgb, "args": (179, 54, 48), "expected": (56, 122, 121)},
                      {"func": gp.colours._hsv_to_hex, "args": (179, 54, 48), "expected": "#387a79"},
                      {"func": gp.colours._hsv_to_cmyk, "args": (179, 54, 48), "expected": (54, 0, 1, 52)},
                      {"func": gp.colours._hsv_to_hsl, "args": (179, 54, 48), "expected": (179, 37, 35)},

                      {"func": gp.colours._hsv_to_rgb, "args": (302, 4, 11), "expected": (28, 27, 28)},
                      {"func": gp.colours._hsv_to_hex, "args": (302, 4, 11), "expected": "#1c1b1c"},
                      {"func": gp.colours._hsv_to_cmyk, "args": (302, 4, 11), "expected": (0, 4, 0, 89)},
                      {"func": gp.colours._hsv_to_hsl, "args": (302, 4, 11), "expected": (302, 2, 11)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict

def test_hsl_converter_functions(_test_function=True):
    functions_dict = [{"func": hsl_to_rgb, "args": (16, 84, 100), "expected": (255, 255, 255)},
                      {"func": hsl_to_hex, "args": (16, 84, 100), "expected": "#ffffff"},
                      {"func": hsl_to_cmyk, "args": (16, 84, 100), "expected": (0, 0, 0, 0)},
                      {"func": hsl_to_hsv, "args": (16, 84, 100), "expected": (16, 0, 100)},

                      {"func": hsl_to_rgb, "args": (66, 32, 76), "expected": (209, 213, 174)},
                      {"func": hsl_to_hex, "args": (66, 32, 76), "expected": "#d1d5ae"},
                      {"func": hsl_to_cmyk, "args": (66, 32, 76), "expected": (2, 0, 18, 16)},
                      {"func": hsl_to_hsv, "args": (66, 32, 76), "expected": (66, 18, 84)},

                      {"func": hsl_to_rgb, "args": (179, 54, 48), "expected": (56, 188, 186)},
                      {"func": hsl_to_hex, "args": (179, 54, 48), "expected": "#38bcba"},
                      {"func": hsl_to_cmyk, "args": (179, 54, 48), "expected": (70, 0, 1, 26)},
                      {"func": hsl_to_hsv, "args": (179, 54, 48), "expected": (179, 70, 74)},

                      {"func": hsl_to_rgb, "args": (302, 4, 11), "expected": (29, 27, 29)},
                      {"func": hsl_to_hex, "args": (302, 4, 11), "expected": "#1d1b1d"},
                      {"func": hsl_to_cmyk, "args": (302, 4, 11), "expected": (0, 8, 0, 89)},
                      {"func": hsl_to_hsv, "args": (302, 4, 11), "expected": (302, 8, 11)},

                      #

                      {"func": gp.colours._hsl_to_rgb, "args": (16, 84, 100), "expected": (255, 255, 255)},
                      {"func": gp.colours._hsl_to_hex, "args": (16, 84, 100), "expected": "#ffffff"},
                      {"func": gp.colours._hsl_to_cmyk, "args": (16, 84, 100), "expected": (0, 0, 0, 0)},
                      {"func": gp.colours._hsl_to_hsv, "args": (16, 84, 100), "expected": (16, 0, 100)},

                      {"func": gp.colours._hsl_to_rgb, "args": (66, 32, 76), "expected": (209, 213, 174)},
                      {"func": gp.colours._hsl_to_hex, "args": (66, 32, 76), "expected": "#d1d5ae"},
                      {"func": gp.colours._hsl_to_cmyk, "args": (66, 32, 76), "expected": (2, 0, 18, 16)},
                      {"func": gp.colours._hsl_to_hsv, "args": (66, 32, 76), "expected": (66, 18, 84)},

                      {"func": gp.colours._hsl_to_rgb, "args": (179, 54, 48), "expected": (56, 188, 186)},
                      {"func": gp.colours._hsl_to_hex, "args": (179, 54, 48), "expected": "#38bcba"},
                      {"func": gp.colours._hsl_to_cmyk, "args": (179, 54, 48), "expected": (70, 0, 1, 26)},
                      {"func": gp.colours._hsl_to_hsv, "args": (179, 54, 48), "expected": (179, 70, 74)},

                      {"func": gp.colours._hsl_to_rgb, "args": (302, 4, 11), "expected": (29, 27, 29)},
                      {"func": gp.colours._hsl_to_hex, "args": (302, 4, 11), "expected": "#1d1b1d"},
                      {"func": gp.colours._hsl_to_cmyk, "args": (302, 4, 11), "expected": (0, 8, 0, 89)},
                      {"func": gp.colours._hsl_to_hsv, "args": (302, 4, 11), "expected": (302, 8, 11)}]
    
    if _test_function:
        test_functions(functions_dict)
    return functions_dict

def test_colour_converter_functions(_test_function=True):
    functions_dict = test_rgb_converter_functions(_test_function=False) + [None]
    functions_dict += test_hex_converter_functions(_test_function=False) + [None]
    functions_dict += test_cmyk_converter_functions(_test_function=False) + [None]
    functions_dict += test_hsv_converter_functions(_test_function=False) + [None]
    functions_dict += test_hsl_converter_functions(_test_function=False)

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_window_methods(_test_function=True):
    gliding_time = 0.2
    
    window = Window(title="Test Window", width=500, height=500)
    functions_dict = [{"func": Window.__init__, "args": {"self": window, "title": "Test Window",
                                                         "width": 500, "height": 500}, "expected": None},

                      {"func": Window._check__autoflush, "args": (window,), "expected": False},
                      {"func": Window._check__check_open, "args": (window,), "expected": True},
                      {"func": Window.is_closed, "args": (window,), "expected": False},
                      {"func": Window.is_open, "args": (window,), "expected": True},

                      None,

                      {"func": Window.get_pos, "args": (window,), "expected": (0, 0)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 0},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": Window.move_x, "args": (window, 100), "expected": window},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 0)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": Window.move_y, "args": (window, 100), "expected": window},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": Window.move, "args": (window, 100, 100), "expected": window},
                      {"func": Window.update, "args": (window, ), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (200, 200)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 200},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": Window.move_to_x, "args": (window, 100), "expected": window},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 200)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": Window.move_to_y, "args": (window, 100), "expected": window},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": Window.move_to, "args": (window, 50, 50), "expected": window},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (50, 50)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 50},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 50},

                      {"func": Window.move_to_point, "args": (window, [30, 30]), "expected": window},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (30, 30)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 30},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 30},

                      None,

                      {"func": Window.glide_to, "args": (window, 0, 0, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (0, 0)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 0},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": Window.glide_x, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 0)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": Window.glide_y, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": Window.glide, "args": (window, 100, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (200, 200)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 200},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": Window.glide_to_x, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 200)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": Window.glide_to_y, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": Window.glide_to_point, "args": (window, [30, 30], gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": Window.update, "args": (window,), "expected": window},
                      {"func": Window.get_pos, "args": (window,), "expected": (30, 30)},
                      {"func": Window.get_x_pos, "args": (window,), "expected": 30},
                      {"func": Window.get_y_pos, "args": (window,), "expected": 30},

                      None,

                      {"func": Window.get_background, "args": (window,), "expected": "#ffffff"},
                      {"func": Window.set_background, "args": (window, "#000000"), "expected": window},
                      {"func": Window.get_background, "args": (window,), "expected": "#000000"},
                      {"func": Window.set_background, "args": (window, ColourRGB(255, 0, 0)), "expected": window},
                      {"func": Window.get_background, "args": (window,), "expected": "#ff0000"},

                      {"func": Window.get_border_width, "args": (window,), "expected": 0},
                      {"func": Window.set_border_width, "args": (window, 2), "expected": window},
                      {"func": Window.get_border_width, "args": (window,), "expected": 2},
                      {"func": Window.set_border_width, "args": (window, 3.5), "expected": window},
                      {"func": Window.get_border_width, "args": (window,), "expected": 3.5},

                      {"func": Window.get_border_relief, "args": (window,), "expected": "flat"}] + [

                      test for relief in BORDER_RELIEFS for test in
                      ({"func": Window.set_border_relief, "args": (window, relief), "expected": window},
                       {"func": Window.get_border_relief, "args": (window,), "expected": relief})] + [

                      {"func": Window.get_window_cursor, "args": (window,), "expected": "arrow"}] + [

                      test for cursor in CURSORS for test in
                      ({"func": Window.set_cursor, "args": (window, cursor), "expected": window},
                       {"func": Window.get_window_cursor, "args": (window,), "expected": cursor})] + [

                      {"func": Window.get_current_cursor, "args": (window,), "expected": "arrow"},

                      {"func": Window.get_draggable, "args": (window,), "expected": (False, False)},
                      {"func": Window.get_x_draggable, "args": (window,), "expected": False},
                      {"func": Window.get_y_draggable, "args": (window,), "expected": False},

                      {"func": Window.set_draggable_x, "args": (window, True), "expected": window},
                      {"func": Window.get_draggable, "args": (window,), "expected": (True, False)},
                      {"func": Window.get_x_draggable, "args": (window,), "expected": True},
                      {"func": Window.get_y_draggable, "args": (window,), "expected": False},

                      {"func": Window.set_draggable_y, "args": (window, True), "expected": window},
                      {"func": Window.get_draggable, "args": (window,), "expected": (True, True)},
                      {"func": Window.get_x_draggable, "args": (window,), "expected": True},
                      {"func": Window.get_y_draggable, "args": (window,), "expected": True},

                      {"func": Window.set_draggable, "args": (window, False), "expected": window},
                      {"func": Window.get_draggable, "args": (window,), "expected": (False, False)},
                      {"func": Window.get_x_draggable, "args": (window,), "expected": False},
                      {"func": Window.get_y_draggable, "args": (window,), "expected": False},

                      {"func": Window.get_resizable, "args": (window,), "expected": (False, False)},
                      {"func": Window.get_width_resizable, "args": (window,), "expected": False},
                      {"func": Window.get_height_resizable, "args": (window,), "expected": False},

                      {"func": Window.get_size, "args": (window,), "expected": (500, 500)},
                      {"func": Window.get_width, "args": (window,), "expected": 500},
                      {"func": Window.get_height, "args": (window,), "expected": 500},

                      {"func": Window.get_min_size, "args": (window,), "expected": (1, 1)},
                      {"func": Window.get_min_width, "args": (window,), "expected": 1},
                      {"func": Window.get_min_height, "args": (window,), "expected": 1},

                      {"func": Window.get_max_size, "args": (window,), "expected": (None, None)},
                      {"func": Window.get_max_width, "args": (window,), "expected": None},
                      {"func": Window.get_max_height, "args": (window,), "expected": None},

                      {"func": Window.__repr__, "args": (window,), "expected": "Window('Test Window', 500x500)"},
                      {"func": Window.get_title, "args": (window,), "expected": "Test Window"},
                      {"func": Window.set_title, "args": (window, "New Title"), "expected": window},
                      {"func": Window.get_title, "args": (window,), "expected": "New Title"},
                      {"func": Window.__repr__, "args": (window,), "expected": "Window('New Title', 500x500)"},

                      {"func": Window.get_coords, "args": (window,), "expected": ([0, 0], [500, 500])},
                      {"func": Window.get_top_left, "args": (window,), "expected": [0, 0]},
                      {"func": Window.get_top_right, "args": (window,), "expected": [500, 0]},
                      {"func": Window.get_bottom_left, "args": (window,), "expected": [0, 500]},
                      {"func": Window.get_bottom_right, "args": (window,), "expected": [500, 500]},

                      {"func": Window.close, "args": (window,), "expected": window},
                      {"func": Window._check__check_open, "args": (window,), "expected": False},
                      {"func": Window.is_closed, "args": (window,), "expected": True},
                      {"func": Window.is_open, "args": (window,), "expected": False}]

    functions_dict.insert(0, f"Testing {len(set(func['func'] for func in functions_dict if isinstance(func, dict)))} "
                             f"Window functions of {get_subclass_methods(Window)}, "
                             f"{round(100 * len(functions_dict) / get_subclass_methods(Window), 2)}%")

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_all_functions():
    functions_dict = test_colour_converter_functions(_test_function=False)
    functions_dict += test_window_methods(_test_function=False)

    test_functions(functions_dict)

"""
while True:
    print(timeit.timeit("func1()", setup="from __main__ import func1", number=10000000))
    print(timeit.timeit("func2()", setup="from __main__ import func2", number=10000000))
    print(timeit.timeit("func3()", setup="from __main__ import func3", number=10000000))
    print(timeit.timeit("func4()", setup="from __main__ import func4", number=10000000))
    print()
"""

# test_all_functions()
countlines(".")
