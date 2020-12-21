import timeit
import math
import os

from matplotlib import pyplot as plt

from goopylib.c_colours import *

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


countlines("goopylib")

"""
print(rgb_to_hex(255, 100, 40))
print(rgb_to_cmyk(255, 100, 40))
print(rgb_to_hsl(255, 100, 40))
print(rgb_to_hsv(255, 100, 40))
"""
"""
print(hex_to_rgb("#ff6428"))
print(hex_to_cmyk("#ff6428"))
print(hex_to_hsl("#ff6428"))
print(hex_to_hsv("#ff6428"))
"""
"""
print(cmyk_to_rgb(0, 61, 84, 0))
print(cmyk_to_hex(0, 61, 84, 0))
print(cmyk_to_hsl(0, 61, 84, 0))
print(cmyk_to_hsv(0, 61, 84, 0))
"""
"""
print(hsv_to_rgb(17, 84, 100))
print(hsv_to_hex(17, 84, 100))
print(hsv_to_cmyk(17, 84, 100))
print(hsv_to_hsl(17, 84, 100))
"""
"""
print(hsl_to_rgb(17, 100, 58))
print(hsl_to_hex(17, 100, 58))
print(hsl_to_cmyk(17, 100, 58))
print(hsl_to_hsv(17, 100, 58))
"""
"""
while True:
    print(timeit.timeit("func1()", setup="from __main__ import func1", number=10000000))
    print(timeit.timeit("func2()", setup="from __main__ import func2", number=10000000))
    print(timeit.timeit("func3()", setup="from __main__ import func3", number=10000000))
    print(timeit.timeit("func4()", setup="from __main__ import func4", number=10000000))
    print()
"""
