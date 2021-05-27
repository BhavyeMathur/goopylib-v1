import timeit
import time
import os

import goopylib as gp


def countlines(start, lines=0, _header=True, _begin_start=None):
    if _header:
        print('{:>10} |{:>10} | {:<20}'.format('ADDED', 'TOTAL', 'FILE'))
        print('{:->11}|{:->11}|{:->20}'.format('', '', ''))

    for file in os.listdir(start):
        file = os.path.join(start, file)
        if os.path.isfile(file):
            if any(file.endswith(end) for end in (".py", ".c", ".h", ".cfg", ".toml", ".in")):
                if not any(folder in file for folder in ("build", "Examples")):
                    with open(file, 'r') as f:
                        newlines = len(f.readlines())
                        lines += newlines

                        print('{:>10} |{:>10} | {}'.format(newlines, lines, file))

    for file in os.listdir(start):
        file = os.path.join(start, file)
        if os.path.isdir(file):
            lines = countlines(file, lines, _header=False, _begin_start=start)

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


# Testing Colour Functions
def test_rgb_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colours.rgb_to_hex, "args": (255, 100, 40), "expected": "#ff6428"},
                      {"func": gp.colours.rgb_to_cmyk, "args": (255, 100, 40), "expected": (0, 61, 84, 0)},
                      {"func": gp.colours.rgb_to_hsl, "args": (255, 100, 40), "expected": (17, 100, 58)},
                      {"func": gp.colours.rgb_to_hsv, "args": (255, 100, 40), "expected": (17, 84, 100)},

                      {"func": gp.colours.rgb_to_hex, "args": (50, 250, 85), "expected": "#32fa55"},
                      {"func": gp.colours.rgb_to_cmyk, "args": (50, 250, 85), "expected": (80, 0, 66, 2)},
                      {"func": gp.colours.rgb_to_hsl, "args": (50, 250, 85), "expected": (130, 95, 59)},
                      {"func": gp.colours.rgb_to_hsv, "args": (50, 250, 85), "expected": (130, 80, 98)},

                      {"func": gp.colours.rgb_to_hex, "args": (105, 65, 245), "expected": "#6941f5"},
                      {"func": gp.colours.rgb_to_cmyk, "args": (105, 65, 245), "expected": (57, 73, 0, 4)},
                      {"func": gp.colours.rgb_to_hsl, "args": (105, 65, 245), "expected": (253, 90, 61)},
                      {"func": gp.colours.rgb_to_hsv, "args": (105, 65, 245), "expected": (253, 73, 96)},

                      #

                      {"func": gp.colours.rgb_to_hex_nocheck, "args": (255, 100, 40), "expected": "#ff6428"},
                      {"func": gp.colours.rgb_to_cmyk_nocheck, "args": (255, 100, 40), "expected": (0, 61, 84, 0)},
                      {"func": gp.colours.rgb_to_hsl_nocheck, "args": (255, 100, 40), "expected": (17, 100, 58)},
                      {"func": gp.colours.rgb_to_hsv_nocheck, "args": (255, 100, 40), "expected": (17, 84, 100)},

                      {"func": gp.colours.rgb_to_hex_nocheck, "args": (50, 250, 85), "expected": "#32fa55"},
                      {"func": gp.colours.rgb_to_cmyk_nocheck, "args": (50, 250, 85), "expected": (80, 0, 66, 2)},
                      {"func": gp.colours.rgb_to_hsl_nocheck, "args": (50, 250, 85), "expected": (130, 95, 59)},
                      {"func": gp.colours.rgb_to_hsv_nocheck, "args": (50, 250, 85), "expected": (130, 80, 98)},

                      {"func": gp.colours.rgb_to_hex_nocheck, "args": (105, 65, 245), "expected": "#6941f5"},
                      {"func": gp.colours.rgb_to_cmyk_nocheck, "args": (105, 65, 245), "expected": (57, 73, 0, 4)},
                      {"func": gp.colours.rgb_to_hsl_nocheck, "args": (105, 65, 245), "expected": (253, 90, 61)},
                      {"func": gp.colours.rgb_to_hsv_nocheck, "args": (105, 65, 245), "expected": (253, 73, 96)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_hex_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colours.hex_to_rgb, "args": ("#ff6428",), "expected": (255, 100, 40)},
                      {"func": gp.colours.hex_to_cmyk, "args": ("#ff6428",), "expected": (0, 61, 84, 0)},
                      {"func": gp.colours.hex_to_hsl, "args": ("#ff6428",), "expected": (17, 100, 58)},
                      {"func": gp.colours.hex_to_hsv, "args": ("#ff6428",), "expected": (17, 84, 100)},

                      {"func": gp.colours.hex_to_rgb_nocheck, "args": ("#ff6428",), "expected": (255, 100, 40)},
                      {"func": gp.colours.hex_to_cmyk_nocheck, "args": ("#ff6428",), "expected": (0, 61, 84, 0)},
                      {"func": gp.colours.hex_to_hsl_nocheck, "args": ("#ff6428",), "expected": (17, 100, 58)},
                      {"func": gp.colours.hex_to_hsv_nocheck, "args": ("#ff6428",), "expected": (17, 84, 100)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_cmyk_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colours.cmyk_to_rgb, "args": (0, 61, 84, 0), "expected": (255, 99, 41)},
                      {"func": gp.colours.cmyk_to_hex, "args": (0, 61, 84, 0), "expected": "#ff6329"},
                      {"func": gp.colours.cmyk_to_hsl, "args": (0, 61, 84, 0), "expected": (16, 100, 58)},
                      {"func": gp.colours.cmyk_to_hsv, "args": (0, 61, 84, 0), "expected": (16, 84, 100)},

                      {"func": gp.colours.cmyk_to_rgb, "args": (64, 0, 10, 25), "expected": (69, 191, 172)},
                      {"func": gp.colours.cmyk_to_hex, "args": (64, 0, 10, 25), "expected": "#45bfac"},
                      {"func": gp.colours.cmyk_to_hsl, "args": (64, 0, 10, 25), "expected": (171, 49, 51)},
                      {"func": gp.colours.cmyk_to_hsv, "args": (64, 0, 10, 25), "expected": (171, 64, 75)},

                      {"func": gp.colours.cmyk_to_rgb, "args": (12, 17, 0, 55), "expected": (101, 95, 115)},
                      {"func": gp.colours.cmyk_to_hex, "args": (12, 17, 0, 55), "expected": "#655f73"},
                      {"func": gp.colours.cmyk_to_hsl, "args": (12, 17, 0, 55), "expected": (258, 9, 41)},
                      {"func": gp.colours.cmyk_to_hsv, "args": (12, 17, 0, 55), "expected": (258, 17, 45)},

                      {"func": gp.colours.cmyk_to_rgb, "args": (87, 79, 0, 74), "expected": (9, 14, 66)},
                      {"func": gp.colours.cmyk_to_hex, "args": (87, 79, 0, 74), "expected": "#090e42"},
                      {"func": gp.colours.cmyk_to_hsl, "args": (87, 79, 0, 74), "expected": (234, 77, 15)},
                      {"func": gp.colours.cmyk_to_hsv, "args": (87, 79, 0, 74), "expected": (234, 87, 26)},

                      #

                      {"func": gp.colours.cmyk_to_rgb_nocheck, "args": (0, 61, 84, 0), "expected": (255, 99, 41)},
                      {"func": gp.colours.cmyk_to_hex_nocheck, "args": (0, 61, 84, 0), "expected": "#ff6329"},
                      {"func": gp.colours.cmyk_to_hsl_nocheck, "args": (0, 61, 84, 0), "expected": (16, 100, 58)},
                      {"func": gp.colours.cmyk_to_hsv_nocheck, "args": (0, 61, 84, 0), "expected": (16, 84, 100)},

                      {"func": gp.colours.cmyk_to_rgb_nocheck, "args": (64, 0, 10, 25), "expected": (69, 191, 172)},
                      {"func": gp.colours.cmyk_to_hex_nocheck, "args": (64, 0, 10, 25), "expected": "#45bfac"},
                      {"func": gp.colours.cmyk_to_hsl_nocheck, "args": (64, 0, 10, 25), "expected": (171, 49, 51)},
                      {"func": gp.colours.cmyk_to_hsv_nocheck, "args": (64, 0, 10, 25), "expected": (171, 64, 75)},

                      {"func": gp.colours.cmyk_to_rgb_nocheck, "args": (12, 17, 0, 55), "expected": (101, 95, 115)},
                      {"func": gp.colours.cmyk_to_hex_nocheck, "args": (12, 17, 0, 55), "expected": "#655f73"},
                      {"func": gp.colours.cmyk_to_hsl_nocheck, "args": (12, 17, 0, 55), "expected": (258, 9, 41)},
                      {"func": gp.colours.cmyk_to_hsv_nocheck, "args": (12, 17, 0, 55), "expected": (258, 17, 45)},

                      {"func": gp.colours.cmyk_to_rgb_nocheck, "args": (87, 79, 0, 74), "expected": (9, 14, 66)},
                      {"func": gp.colours.cmyk_to_hex_nocheck, "args": (87, 79, 0, 74), "expected": "#090e42"},
                      {"func": gp.colours.cmyk_to_hsl_nocheck, "args": (87, 79, 0, 74), "expected": (234, 77, 15)},
                      {"func": gp.colours.cmyk_to_hsv_nocheck, "args": (87, 79, 0, 74), "expected": (234, 87, 26)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_hsv_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colours.hsv_to_rgb, "args": (16, 84, 100), "expected": (255, 98, 41)},
                      {"func": gp.colours.hsv_to_hex, "args": (16, 84, 100), "expected": "#ff6229"},
                      {"func": gp.colours.hsv_to_cmyk, "args": (16, 84, 100), "expected": (0, 62, 84, 0)},
                      {"func": gp.colours.hsv_to_hsl, "args": (16, 84, 100), "expected": (16, 100, 58)},

                      {"func": gp.colours.hsv_to_rgb, "args": (66, 32, 76), "expected": (188, 194, 132)},
                      {"func": gp.colours.hsv_to_hex, "args": (66, 32, 76), "expected": "#bcc284"},
                      {"func": gp.colours.hsv_to_cmyk, "args": (66, 32, 76), "expected": (3, 0, 32, 24)},
                      {"func": gp.colours.hsv_to_hsl, "args": (66, 32, 76), "expected": (66, 34, 64)},

                      {"func": gp.colours.hsv_to_rgb, "args": (179, 54, 48), "expected": (56, 122, 121)},
                      {"func": gp.colours.hsv_to_hex, "args": (179, 54, 48), "expected": "#387a79"},
                      {"func": gp.colours.hsv_to_cmyk, "args": (179, 54, 48), "expected": (54, 0, 1, 52)},
                      {"func": gp.colours.hsv_to_hsl, "args": (179, 54, 48), "expected": (179, 37, 35)},

                      {"func": gp.colours.hsv_to_rgb, "args": (302, 4, 11), "expected": (28, 27, 28)},
                      {"func": gp.colours.hsv_to_hex, "args": (302, 4, 11), "expected": "#1c1b1c"},
                      {"func": gp.colours.hsv_to_cmyk, "args": (302, 4, 11), "expected": (0, 4, 0, 89)},
                      {"func": gp.colours.hsv_to_hsl, "args": (302, 4, 11), "expected": (302, 2, 11)},

                      #

                      {"func": gp.colours.hsv_to_rgb_nocheck, "args": (16, 84, 100), "expected": (255, 98, 41)},
                      {"func": gp.colours.hsv_to_hex_nocheck, "args": (16, 84, 100), "expected": "#ff6229"},
                      {"func": gp.colours.hsv_to_cmyk_nocheck, "args": (16, 84, 100), "expected": (0, 62, 84, 0)},
                      {"func": gp.colours.hsv_to_hsl_nocheck, "args": (16, 84, 100), "expected": (16, 100, 58)},

                      {"func": gp.colours.hsv_to_rgb_nocheck, "args": (66, 32, 76), "expected": (188, 194, 132)},
                      {"func": gp.colours.hsv_to_hex_nocheck, "args": (66, 32, 76), "expected": "#bcc284"},
                      {"func": gp.colours.hsv_to_cmyk_nocheck, "args": (66, 32, 76), "expected": (3, 0, 32, 24)},
                      {"func": gp.colours.hsv_to_hsl_nocheck, "args": (66, 32, 76), "expected": (66, 34, 64)},

                      {"func": gp.colours.hsv_to_rgb_nocheck, "args": (179, 54, 48), "expected": (56, 122, 121)},
                      {"func": gp.colours.hsv_to_hex_nocheck, "args": (179, 54, 48), "expected": "#387a79"},
                      {"func": gp.colours.hsv_to_cmyk_nocheck, "args": (179, 54, 48), "expected": (54, 0, 1, 52)},
                      {"func": gp.colours.hsv_to_hsl_nocheck, "args": (179, 54, 48), "expected": (179, 37, 35)},

                      {"func": gp.colours.hsv_to_rgb_nocheck, "args": (302, 4, 11), "expected": (28, 27, 28)},
                      {"func": gp.colours.hsv_to_hex_nocheck, "args": (302, 4, 11), "expected": "#1c1b1c"},
                      {"func": gp.colours.hsv_to_cmyk_nocheck, "args": (302, 4, 11), "expected": (0, 4, 0, 89)},
                      {"func": gp.colours.hsv_to_hsl_nocheck, "args": (302, 4, 11), "expected": (302, 2, 11)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_hsl_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colours.hsl_to_rgb, "args": (16, 84, 100), "expected": (255, 255, 255)},
                      {"func": gp.colours.hsl_to_hex, "args": (16, 84, 100), "expected": "#ffffff"},
                      {"func": gp.colours.hsl_to_cmyk, "args": (16, 84, 100), "expected": (0, 0, 0, 0)},
                      {"func": gp.colours.hsl_to_hsv, "args": (16, 84, 100), "expected": (16, 0, 100)},

                      {"func": gp.colours.hsl_to_rgb, "args": (66, 32, 76), "expected": (209, 213, 174)},
                      {"func": gp.colours.hsl_to_hex, "args": (66, 32, 76), "expected": "#d1d5ae"},
                      {"func": gp.colours.hsl_to_cmyk, "args": (66, 32, 76), "expected": (2, 0, 18, 16)},
                      {"func": gp.colours.hsl_to_hsv, "args": (66, 32, 76), "expected": (66, 18, 84)},

                      {"func": gp.colours.hsl_to_rgb, "args": (179, 54, 48), "expected": (56, 188, 186)},
                      {"func": gp.colours.hsl_to_hex, "args": (179, 54, 48), "expected": "#38bcba"},
                      {"func": gp.colours.hsl_to_cmyk, "args": (179, 54, 48), "expected": (70, 0, 1, 26)},
                      {"func": gp.colours.hsl_to_hsv, "args": (179, 54, 48), "expected": (179, 70, 74)},

                      {"func": gp.colours.hsl_to_rgb, "args": (302, 4, 11), "expected": (29, 27, 29)},
                      {"func": gp.colours.hsl_to_hex, "args": (302, 4, 11), "expected": "#1d1b1d"},
                      {"func": gp.colours.hsl_to_cmyk, "args": (302, 4, 11), "expected": (0, 8, 0, 89)},
                      {"func": gp.colours.hsl_to_hsv, "args": (302, 4, 11), "expected": (302, 8, 11)},

                      #

                      {"func": gp.colours.hsl_to_rgb_nocheck, "args": (16, 84, 100), "expected": (255, 255, 255)},
                      {"func": gp.colours.hsl_to_hex_nocheck, "args": (16, 84, 100), "expected": "#ffffff"},
                      {"func": gp.colours.hsl_to_cmyk_nocheck, "args": (16, 84, 100), "expected": (0, 0, 0, 0)},
                      {"func": gp.colours.hsl_to_hsv_nocheck, "args": (16, 84, 100), "expected": (16, 0, 100)},

                      {"func": gp.colours.hsl_to_rgb_nocheck, "args": (66, 32, 76), "expected": (209, 213, 174)},
                      {"func": gp.colours.hsl_to_hex_nocheck, "args": (66, 32, 76), "expected": "#d1d5ae"},
                      {"func": gp.colours.hsl_to_cmyk_nocheck, "args": (66, 32, 76), "expected": (2, 0, 18, 16)},
                      {"func": gp.colours.hsl_to_hsv_nocheck, "args": (66, 32, 76), "expected": (66, 18, 84)},

                      {"func": gp.colours.hsl_to_rgb_nocheck, "args": (179, 54, 48), "expected": (56, 188, 186)},
                      {"func": gp.colours.hsl_to_hex_nocheck, "args": (179, 54, 48), "expected": "#38bcba"},
                      {"func": gp.colours.hsl_to_cmyk_nocheck, "args": (179, 54, 48), "expected": (70, 0, 1, 26)},
                      {"func": gp.colours.hsl_to_hsv_nocheck, "args": (179, 54, 48), "expected": (179, 70, 74)},

                      {"func": gp.colours.hsl_to_rgb_nocheck, "args": (302, 4, 11), "expected": (29, 27, 29)},
                      {"func": gp.colours.hsl_to_hex_nocheck, "args": (302, 4, 11), "expected": "#1d1b1d"},
                      {"func": gp.colours.hsl_to_cmyk_nocheck, "args": (302, 4, 11), "expected": (0, 8, 0, 89)},
                      {"func": gp.colours.hsl_to_hsv_nocheck, "args": (302, 4, 11), "expected": (302, 8, 11)}]
    
    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_colour_converter_functions(_test_function=True):
    functions_dict = test_rgb_converter_functions(_test_function=False) + [None]
    functions_dict += test_hex_converter_functions(_test_function=False) + [None]
    functions_dict += test_cmyk_converter_functions(_test_function=False) + [None]
    functions_dict += test_hsv_converter_functions(_test_function=False) + [None]
    functions_dict += test_hsl_converter_functions(_test_function=False) + [None]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


# Testing American Spelling (Color) Colour Functions
def test_american_rgb_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colors.rgb_to_hex, "args": (255, 100, 40), "expected": "#ff6428"},
                      {"func": gp.colors.rgb_to_cmyk, "args": (255, 100, 40), "expected": (0, 61, 84, 0)},
                      {"func": gp.colors.rgb_to_hsl, "args": (255, 100, 40), "expected": (17, 100, 58)},
                      {"func": gp.colors.rgb_to_hsv, "args": (255, 100, 40), "expected": (17, 84, 100)},

                      {"func": gp.colors.rgb_to_hex, "args": (50, 250, 85), "expected": "#32fa55"},
                      {"func": gp.colors.rgb_to_cmyk, "args": (50, 250, 85), "expected": (80, 0, 66, 2)},
                      {"func": gp.colors.rgb_to_hsl, "args": (50, 250, 85), "expected": (130, 95, 59)},
                      {"func": gp.colors.rgb_to_hsv, "args": (50, 250, 85), "expected": (130, 80, 98)},

                      {"func": gp.colors.rgb_to_hex, "args": (105, 65, 245), "expected": "#6941f5"},
                      {"func": gp.colors.rgb_to_cmyk, "args": (105, 65, 245), "expected": (57, 73, 0, 4)},
                      {"func": gp.colors.rgb_to_hsl, "args": (105, 65, 245), "expected": (253, 90, 61)},
                      {"func": gp.colors.rgb_to_hsv, "args": (105, 65, 245), "expected": (253, 73, 96)},

                      #

                      {"func": gp.colors.rgb_to_hex_nocheck, "args": (255, 100, 40), "expected": "#ff6428"},
                      {"func": gp.colors.rgb_to_cmyk_nocheck, "args": (255, 100, 40), "expected": (0, 61, 84, 0)},
                      {"func": gp.colors.rgb_to_hsl_nocheck, "args": (255, 100, 40), "expected": (17, 100, 58)},
                      {"func": gp.colors.rgb_to_hsv_nocheck, "args": (255, 100, 40), "expected": (17, 84, 100)},

                      {"func": gp.colors.rgb_to_hex_nocheck, "args": (50, 250, 85), "expected": "#32fa55"},
                      {"func": gp.colors.rgb_to_cmyk_nocheck, "args": (50, 250, 85), "expected": (80, 0, 66, 2)},
                      {"func": gp.colors.rgb_to_hsl_nocheck, "args": (50, 250, 85), "expected": (130, 95, 59)},
                      {"func": gp.colors.rgb_to_hsv_nocheck, "args": (50, 250, 85), "expected": (130, 80, 98)},

                      {"func": gp.colors.rgb_to_hex_nocheck, "args": (105, 65, 245), "expected": "#6941f5"},
                      {"func": gp.colors.rgb_to_cmyk_nocheck, "args": (105, 65, 245), "expected": (57, 73, 0, 4)},
                      {"func": gp.colors.rgb_to_hsl_nocheck, "args": (105, 65, 245), "expected": (253, 90, 61)},
                      {"func": gp.colors.rgb_to_hsv_nocheck, "args": (105, 65, 245), "expected": (253, 73, 96)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_american_hex_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colors.hex_to_rgb, "args": ("#ff6428",), "expected": (255, 100, 40)},
                      {"func": gp.colors.hex_to_cmyk, "args": ("#ff6428",), "expected": (0, 61, 84, 0)},
                      {"func": gp.colors.hex_to_hsl, "args": ("#ff6428",), "expected": (17, 100, 58)},
                      {"func": gp.colors.hex_to_hsv, "args": ("#ff6428",), "expected": (17, 84, 100)},

                      {"func": gp.colors.hex_to_rgb_nocheck, "args": ("#ff6428",), "expected": (255, 100, 40)},
                      {"func": gp.colors.hex_to_cmyk_nocheck, "args": ("#ff6428",), "expected": (0, 61, 84, 0)},
                      {"func": gp.colors.hex_to_hsl_nocheck, "args": ("#ff6428",), "expected": (17, 100, 58)},
                      {"func": gp.colors.hex_to_hsv_nocheck, "args": ("#ff6428",), "expected": (17, 84, 100)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_american_cmyk_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colors.cmyk_to_rgb, "args": (0, 61, 84, 0), "expected": (255, 99, 41)},
                      {"func": gp.colors.cmyk_to_hex, "args": (0, 61, 84, 0), "expected": "#ff6329"},
                      {"func": gp.colors.cmyk_to_hsl, "args": (0, 61, 84, 0), "expected": (16, 100, 58)},
                      {"func": gp.colors.cmyk_to_hsv, "args": (0, 61, 84, 0), "expected": (16, 84, 100)},

                      {"func": gp.colors.cmyk_to_rgb, "args": (64, 0, 10, 25), "expected": (69, 191, 172)},
                      {"func": gp.colors.cmyk_to_hex, "args": (64, 0, 10, 25), "expected": "#45bfac"},
                      {"func": gp.colors.cmyk_to_hsl, "args": (64, 0, 10, 25), "expected": (171, 49, 51)},
                      {"func": gp.colors.cmyk_to_hsv, "args": (64, 0, 10, 25), "expected": (171, 64, 75)},

                      {"func": gp.colors.cmyk_to_rgb, "args": (12, 17, 0, 55), "expected": (101, 95, 115)},
                      {"func": gp.colors.cmyk_to_hex, "args": (12, 17, 0, 55), "expected": "#655f73"},
                      {"func": gp.colors.cmyk_to_hsl, "args": (12, 17, 0, 55), "expected": (258, 9, 41)},
                      {"func": gp.colors.cmyk_to_hsv, "args": (12, 17, 0, 55), "expected": (258, 17, 45)},

                      {"func": gp.colors.cmyk_to_rgb, "args": (87, 79, 0, 74), "expected": (9, 14, 66)},
                      {"func": gp.colors.cmyk_to_hex, "args": (87, 79, 0, 74), "expected": "#090e42"},
                      {"func": gp.colors.cmyk_to_hsl, "args": (87, 79, 0, 74), "expected": (234, 77, 15)},
                      {"func": gp.colors.cmyk_to_hsv, "args": (87, 79, 0, 74), "expected": (234, 87, 26)},

                      #

                      {"func": gp.colors.cmyk_to_rgb_nocheck, "args": (0, 61, 84, 0), "expected": (255, 99, 41)},
                      {"func": gp.colors.cmyk_to_hex_nocheck, "args": (0, 61, 84, 0), "expected": "#ff6329"},
                      {"func": gp.colors.cmyk_to_hsl_nocheck, "args": (0, 61, 84, 0), "expected": (16, 100, 58)},
                      {"func": gp.colors.cmyk_to_hsv_nocheck, "args": (0, 61, 84, 0), "expected": (16, 84, 100)},

                      {"func": gp.colors.cmyk_to_rgb_nocheck, "args": (64, 0, 10, 25), "expected": (69, 191, 172)},
                      {"func": gp.colors.cmyk_to_hex_nocheck, "args": (64, 0, 10, 25), "expected": "#45bfac"},
                      {"func": gp.colors.cmyk_to_hsl_nocheck, "args": (64, 0, 10, 25), "expected": (171, 49, 51)},
                      {"func": gp.colors.cmyk_to_hsv_nocheck, "args": (64, 0, 10, 25), "expected": (171, 64, 75)},

                      {"func": gp.colors.cmyk_to_rgb_nocheck, "args": (12, 17, 0, 55), "expected": (101, 95, 115)},
                      {"func": gp.colors.cmyk_to_hex_nocheck, "args": (12, 17, 0, 55), "expected": "#655f73"},
                      {"func": gp.colors.cmyk_to_hsl_nocheck, "args": (12, 17, 0, 55), "expected": (258, 9, 41)},
                      {"func": gp.colors.cmyk_to_hsv_nocheck, "args": (12, 17, 0, 55), "expected": (258, 17, 45)},

                      {"func": gp.colors.cmyk_to_rgb_nocheck, "args": (87, 79, 0, 74), "expected": (9, 14, 66)},
                      {"func": gp.colors.cmyk_to_hex_nocheck, "args": (87, 79, 0, 74), "expected": "#090e42"},
                      {"func": gp.colors.cmyk_to_hsl_nocheck, "args": (87, 79, 0, 74), "expected": (234, 77, 15)},
                      {"func": gp.colors.cmyk_to_hsv_nocheck, "args": (87, 79, 0, 74), "expected": (234, 87, 26)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_american_hsv_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colors.hsv_to_rgb, "args": (16, 84, 100), "expected": (255, 98, 41)},
                      {"func": gp.colors.hsv_to_hex, "args": (16, 84, 100), "expected": "#ff6229"},
                      {"func": gp.colors.hsv_to_cmyk, "args": (16, 84, 100), "expected": (0, 62, 84, 0)},
                      {"func": gp.colors.hsv_to_hsl, "args": (16, 84, 100), "expected": (16, 100, 58)},

                      {"func": gp.colors.hsv_to_rgb, "args": (66, 32, 76), "expected": (188, 194, 132)},
                      {"func": gp.colors.hsv_to_hex, "args": (66, 32, 76), "expected": "#bcc284"},
                      {"func": gp.colors.hsv_to_cmyk, "args": (66, 32, 76), "expected": (3, 0, 32, 24)},
                      {"func": gp.colors.hsv_to_hsl, "args": (66, 32, 76), "expected": (66, 34, 64)},

                      {"func": gp.colors.hsv_to_rgb, "args": (179, 54, 48), "expected": (56, 122, 121)},
                      {"func": gp.colors.hsv_to_hex, "args": (179, 54, 48), "expected": "#387a79"},
                      {"func": gp.colors.hsv_to_cmyk, "args": (179, 54, 48), "expected": (54, 0, 1, 52)},
                      {"func": gp.colors.hsv_to_hsl, "args": (179, 54, 48), "expected": (179, 37, 35)},

                      {"func": gp.colors.hsv_to_rgb, "args": (302, 4, 11), "expected": (28, 27, 28)},
                      {"func": gp.colors.hsv_to_hex, "args": (302, 4, 11), "expected": "#1c1b1c"},
                      {"func": gp.colors.hsv_to_cmyk, "args": (302, 4, 11), "expected": (0, 4, 0, 89)},
                      {"func": gp.colors.hsv_to_hsl, "args": (302, 4, 11), "expected": (302, 2, 11)},

                      #

                      {"func": gp.colors.hsv_to_rgb_nocheck, "args": (16, 84, 100), "expected": (255, 98, 41)},
                      {"func": gp.colors.hsv_to_hex_nocheck, "args": (16, 84, 100), "expected": "#ff6229"},
                      {"func": gp.colors.hsv_to_cmyk_nocheck, "args": (16, 84, 100), "expected": (0, 62, 84, 0)},
                      {"func": gp.colors.hsv_to_hsl_nocheck, "args": (16, 84, 100), "expected": (16, 100, 58)},

                      {"func": gp.colors.hsv_to_rgb_nocheck, "args": (66, 32, 76), "expected": (188, 194, 132)},
                      {"func": gp.colors.hsv_to_hex_nocheck, "args": (66, 32, 76), "expected": "#bcc284"},
                      {"func": gp.colors.hsv_to_cmyk_nocheck, "args": (66, 32, 76), "expected": (3, 0, 32, 24)},
                      {"func": gp.colors.hsv_to_hsl_nocheck, "args": (66, 32, 76), "expected": (66, 34, 64)},

                      {"func": gp.colors.hsv_to_rgb_nocheck, "args": (179, 54, 48), "expected": (56, 122, 121)},
                      {"func": gp.colors.hsv_to_hex_nocheck, "args": (179, 54, 48), "expected": "#387a79"},
                      {"func": gp.colors.hsv_to_cmyk_nocheck, "args": (179, 54, 48), "expected": (54, 0, 1, 52)},
                      {"func": gp.colors.hsv_to_hsl_nocheck, "args": (179, 54, 48), "expected": (179, 37, 35)},

                      {"func": gp.colors.hsv_to_rgb_nocheck, "args": (302, 4, 11), "expected": (28, 27, 28)},
                      {"func": gp.colors.hsv_to_hex_nocheck, "args": (302, 4, 11), "expected": "#1c1b1c"},
                      {"func": gp.colors.hsv_to_cmyk_nocheck, "args": (302, 4, 11), "expected": (0, 4, 0, 89)},
                      {"func": gp.colors.hsv_to_hsl_nocheck, "args": (302, 4, 11), "expected": (302, 2, 11)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_american_hsl_converter_functions(_test_function=True):
    functions_dict = [{"func": gp.colors.hsl_to_rgb, "args": (16, 84, 100), "expected": (255, 255, 255)},
                      {"func": gp.colors.hsl_to_hex, "args": (16, 84, 100), "expected": "#ffffff"},
                      {"func": gp.colors.hsl_to_cmyk, "args": (16, 84, 100), "expected": (0, 0, 0, 0)},
                      {"func": gp.colors.hsl_to_hsv, "args": (16, 84, 100), "expected": (16, 0, 100)},

                      {"func": gp.colors.hsl_to_rgb, "args": (66, 32, 76), "expected": (209, 213, 174)},
                      {"func": gp.colors.hsl_to_hex, "args": (66, 32, 76), "expected": "#d1d5ae"},
                      {"func": gp.colors.hsl_to_cmyk, "args": (66, 32, 76), "expected": (2, 0, 18, 16)},
                      {"func": gp.colors.hsl_to_hsv, "args": (66, 32, 76), "expected": (66, 18, 84)},

                      {"func": gp.colors.hsl_to_rgb, "args": (179, 54, 48), "expected": (56, 188, 186)},
                      {"func": gp.colors.hsl_to_hex, "args": (179, 54, 48), "expected": "#38bcba"},
                      {"func": gp.colors.hsl_to_cmyk, "args": (179, 54, 48), "expected": (70, 0, 1, 26)},
                      {"func": gp.colors.hsl_to_hsv, "args": (179, 54, 48), "expected": (179, 70, 74)},

                      {"func": gp.colors.hsl_to_rgb, "args": (302, 4, 11), "expected": (29, 27, 29)},
                      {"func": gp.colors.hsl_to_hex, "args": (302, 4, 11), "expected": "#1d1b1d"},
                      {"func": gp.colors.hsl_to_cmyk, "args": (302, 4, 11), "expected": (0, 8, 0, 89)},
                      {"func": gp.colors.hsl_to_hsv, "args": (302, 4, 11), "expected": (302, 8, 11)},

                      #

                      {"func": gp.colors.hsl_to_rgb_nocheck, "args": (16, 84, 100), "expected": (255, 255, 255)},
                      {"func": gp.colors.hsl_to_hex_nocheck, "args": (16, 84, 100), "expected": "#ffffff"},
                      {"func": gp.colors.hsl_to_cmyk_nocheck, "args": (16, 84, 100), "expected": (0, 0, 0, 0)},
                      {"func": gp.colors.hsl_to_hsv_nocheck, "args": (16, 84, 100), "expected": (16, 0, 100)},

                      {"func": gp.colors.hsl_to_rgb_nocheck, "args": (66, 32, 76), "expected": (209, 213, 174)},
                      {"func": gp.colors.hsl_to_hex_nocheck, "args": (66, 32, 76), "expected": "#d1d5ae"},
                      {"func": gp.colors.hsl_to_cmyk_nocheck, "args": (66, 32, 76), "expected": (2, 0, 18, 16)},
                      {"func": gp.colors.hsl_to_hsv_nocheck, "args": (66, 32, 76), "expected": (66, 18, 84)},

                      {"func": gp.colors.hsl_to_rgb_nocheck, "args": (179, 54, 48), "expected": (56, 188, 186)},
                      {"func": gp.colors.hsl_to_hex_nocheck, "args": (179, 54, 48), "expected": "#38bcba"},
                      {"func": gp.colors.hsl_to_cmyk_nocheck, "args": (179, 54, 48), "expected": (70, 0, 1, 26)},
                      {"func": gp.colors.hsl_to_hsv_nocheck, "args": (179, 54, 48), "expected": (179, 70, 74)},

                      {"func": gp.colors.hsl_to_rgb_nocheck, "args": (302, 4, 11), "expected": (29, 27, 29)},
                      {"func": gp.colors.hsl_to_hex_nocheck, "args": (302, 4, 11), "expected": "#1d1b1d"},
                      {"func": gp.colors.hsl_to_cmyk_nocheck, "args": (302, 4, 11), "expected": (0, 8, 0, 89)},
                      {"func": gp.colors.hsl_to_hsv_nocheck, "args": (302, 4, 11), "expected": (302, 8, 11)}]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_color_converter_functions(_test_function=True):
    functions_dict = test_american_rgb_converter_functions(_test_function=False) + [None]
    functions_dict += test_american_hex_converter_functions(_test_function=False) + [None]
    functions_dict += test_american_cmyk_converter_functions(_test_function=False) + [None]
    functions_dict += test_american_hsv_converter_functions(_test_function=False) + [None]
    functions_dict += test_american_hsl_converter_functions(_test_function=False) + [None]

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


# Testing the Window class
def test_window_methods(_test_function=True):
    gliding_time = 0.2
    
    window = gp.Window(title="Test Window", width=500, height=500)
    functions_dict = [{"func": gp.Window.__init__, "args": {"self": window, "title": "Test Window",
                       "width": 500, "height": 500}, "expected": None},

                      {"func": gp.Window._check__autoflush, "args": (window,), "expected": False},
                      {"func": gp.Window._check__check_open, "args": (window,), "expected": True},
                      {"func": gp.Window.is_closed, "args": (window,), "expected": False},
                      {"func": gp.Window.is_open, "args": (window,), "expected": True},

                      None,

                      {"func": gp.Window.get_pos, "args": (window,), "expected": (0, 0)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 0},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": gp.Window.move_x, "args": (window, 100), "expected": window},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 0)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": gp.Window.move_y, "args": (window, 100), "expected": window},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": gp.Window.move, "args": (window, 100, 100), "expected": window},
                      {"func": gp.Window.update, "args": (window, ), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (200, 200)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 200},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": gp.Window.move_to_x, "args": (window, 100), "expected": window},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 200)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": gp.Window.move_to_y, "args": (window, 100), "expected": window},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": gp.Window.move_to, "args": (window, 50, 50), "expected": window},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (50, 50)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 50},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 50},

                      {"func": gp.Window.move_to_point, "args": (window, [30, 30]), "expected": window},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (30, 30)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 30},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 30},

                      None,

                      {"func": gp.Window.glide_to, "args": (window, 0, 0, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (0, 0)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 0},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": gp.Window.glide_x, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 0)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 0},

                      {"func": gp.Window.glide_y, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": gp.Window.glide, "args": (window, 100, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (200, 200)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 200},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": gp.Window.glide_to_x, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 200)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 200},

                      {"func": gp.Window.glide_to_y, "args": (window, 100, gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (100, 100)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 100},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 100},

                      {"func": gp.Window.glide_to_point, "args": (window, [30, 30], gliding_time), "expected": window},
                      {"func": time.sleep, "args": (gliding_time,), "expected": None},
                      {"func": gp.Window.update, "args": (window,), "expected": window},
                      {"func": gp.Window.get_pos, "args": (window,), "expected": (30, 30)},
                      {"func": gp.Window.get_x_pos, "args": (window,), "expected": 30},
                      {"func": gp.Window.get_y_pos, "args": (window,), "expected": 30},

                      None,

                      {"func": gp.Window.get_background, "args": (window,), "expected": "#ffffff"},
                      {"func": gp.Window.set_background, "args": (window, "#000000"), "expected": window},
                      {"func": gp.Window.get_background, "args": (window,), "expected": "#000000"},
                      {"func": gp.Window.set_background, "args": (window, gp.colours.ColourRGB(255, 0, 0)), 
                       "expected": window},
                      {"func": gp.Window.get_background, "args": (window,), "expected": "#ff0000"},

                      {"func": gp.Window.get_border_width, "args": (window,), "expected": 0},
                      {"func": gp.Window.set_border_width, "args": (window, 2), "expected": window},
                      {"func": gp.Window.get_border_width, "args": (window,), "expected": 2},
                      {"func": gp.Window.set_border_width, "args": (window, 3.5), "expected": window},
                      {"func": gp.Window.get_border_width, "args": (window,), "expected": 3.5},

                      {"func": gp.Window.get_border_relief, "args": (window,), "expected": "flat"}] + [

                      test for relief in gp.constants.BORDER_RELIEFS for test in
                      ({"func": gp.Window.set_border_relief, "args": (window, relief), "expected": window},
                       {"func": gp.Window.get_border_relief, "args": (window,), "expected": relief})] + [

                      {"func": gp.Window.get_window_cursor, "args": (window,), "expected": "arrow"}] + [

                      test for cursor in gp.constants.CURSORS for test in
                      ({"func": gp.Window.set_cursor, "args": (window, cursor), "expected": window},
                       {"func": gp.Window.get_window_cursor, "args": (window,), "expected": cursor})] + [

                      {"func": gp.Window.get_current_cursor, "args": (window,), "expected": "arrow"},

                      {"func": gp.Window.get_draggable, "args": (window,), "expected": (False, False)},
                      {"func": gp.Window.get_x_draggable, "args": (window,), "expected": False},
                      {"func": gp.Window.get_y_draggable, "args": (window,), "expected": False},

                      {"func": gp.Window.set_draggable_x, "args": (window, True), "expected": window},
                      {"func": gp.Window.get_draggable, "args": (window,), "expected": (True, False)},
                      {"func": gp.Window.get_x_draggable, "args": (window,), "expected": True},
                      {"func": gp.Window.get_y_draggable, "args": (window,), "expected": False},

                      {"func": gp.Window.set_draggable_y, "args": (window, True), "expected": window},
                      {"func": gp.Window.get_draggable, "args": (window,), "expected": (True, True)},
                      {"func": gp.Window.get_x_draggable, "args": (window,), "expected": True},
                      {"func": gp.Window.get_y_draggable, "args": (window,), "expected": True},

                      {"func": gp.Window.set_draggable, "args": (window, False), "expected": window},
                      {"func": gp.Window.get_draggable, "args": (window,), "expected": (False, False)},
                      {"func": gp.Window.get_x_draggable, "args": (window,), "expected": False},
                      {"func": gp.Window.get_y_draggable, "args": (window,), "expected": False},

                      {"func": gp.Window.get_resizable, "args": (window,), "expected": (False, False)},
                      {"func": gp.Window.get_width_resizable, "args": (window,), "expected": False},
                      {"func": gp.Window.get_height_resizable, "args": (window,), "expected": False},

                      {"func": gp.Window.get_size, "args": (window,), "expected": (500, 500)},
                      {"func": gp.Window.get_width, "args": (window,), "expected": 500},
                      {"func": gp.Window.get_height, "args": (window,), "expected": 500},

                      {"func": gp.Window.get_min_size, "args": (window,), "expected": (1, 1)},
                      {"func": gp.Window.get_min_width, "args": (window,), "expected": 1},
                      {"func": gp.Window.get_min_height, "args": (window,), "expected": 1},

                      {"func": gp.Window.get_max_size, "args": (window,), "expected": (None, None)},
                      {"func": gp.Window.get_max_width, "args": (window,), "expected": None},
                      {"func": gp.Window.get_max_height, "args": (window,), "expected": None},

                      {"func": gp.Window.__repr__, "args": (window,), "expected": "Window('Test Window', 500x500)"},
                      {"func": gp.Window.get_title, "args": (window,), "expected": "Test Window"},
                      {"func": gp.Window.set_title, "args": (window, "New Title"), "expected": window},
                      {"func": gp.Window.get_title, "args": (window,), "expected": "New Title"},
                      {"func": gp.Window.__repr__, "args": (window,), "expected": "Window('New Title', 500x500)"},

                      {"func": gp.Window.get_coords, "args": (window,), "expected": ([0, 0], [500, 500])},
                      {"func": gp.Window.get_top_left, "args": (window,), "expected": [0, 0]},
                      {"func": gp.Window.get_top_right, "args": (window,), "expected": [500, 0]},
                      {"func": gp.Window.get_bottom_left, "args": (window,), "expected": [0, 500]},
                      {"func": gp.Window.get_bottom_right, "args": (window,), "expected": [500, 500]},

                      {"func": gp.Window.close, "args": (window,), "expected": window},
                      {"func": gp.Window._check__check_open, "args": (window,), "expected": False},
                      {"func": gp.Window.is_closed, "args": (window,), "expected": True},
                      {"func": gp.Window.is_open, "args": (window,), "expected": False}]

    functions_dict.insert(0, f"Testing {len(set(func['func'] for func in functions_dict if isinstance(func, dict)))} "
                             f"Window functions of {get_subclass_methods(gp.Window)}, "
                             f"{round(100 * len(functions_dict) / get_subclass_methods(gp.Window), 2)}%")

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_bezier_curve_functions(_test_function=True):
    functions_dict = []

    if _test_function:
        test_functions(functions_dict)
    return functions_dict


def test_all_functions():
    functions_dict = test_colour_converter_functions(_test_function=False)
    functions_dict += test_color_converter_functions(_test_function=False)
    functions_dict += test_window_methods(_test_function=False)

    test_functions(functions_dict)


# Testing all goopylib examples
def test_all_examples():
    import Examples.HelloWorld
    import Examples.interpolations_example
    import Examples.bspline_example
    import Examples.triangulation_test

    # import Examples.CalendarDateSelector.Calendar
    # import Examples.SnakeGame.SnakeGame
    # import Examples.PacManAnimation.PacManAnimation
    # import Examples.ModernLoginPage.ModernLoginPage

"""
while True:
    print(timeit.timeit("func1()", setup="from __main__ import func1", number=10000000))
    print(timeit.timeit("func2()", setup="from __main__ import func2", number=10000000))
    print(timeit.timeit("func3()", setup="from __main__ import func3", number=10000000))
    print(timeit.timeit("func4()", setup="from __main__ import func4", number=10000000))
    print()
"""

# test_all_functions()
# test_all_examples()

countlines(".")
