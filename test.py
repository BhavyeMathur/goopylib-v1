import timeit
import math
import os

from matplotlib import pyplot as plt

from goopylib.imports import *


def func1():
    return min([240, 255])


def func2():
    return min(240, 255)


def func3():
    if 260 > 255:
        return 255
    return 240


def func4():
    return 255 if 240 > 255 else 240


def countlines(start, lines=0, header=True, begin_start=None):
    if header:
        print('{:>10} |{:>10} | {:<20}'.format('ADDED', 'TOTAL', 'FILE'))
        print('{:->11}|{:->11}|{:->20}'.format('', '', ''))

    for thing in os.listdir(start):
        thing = os.path.join(start, thing)
        if os.path.isfile(thing):
            if thing.endswith('.py') or thing.endswith('.c'):
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


# countlines("goopylib")

c = ColourRGB(100, 150, 100)
print(isinstance(c, ColorRGB))


"""
while True:
    print(timeit.timeit("func1()", setup="from __main__ import func1", number=10000000))
    print(timeit.timeit("func2()", setup="from __main__ import func2", number=10000000))
    print(timeit.timeit("func3()", setup="from __main__ import func3", number=10000000))
    print(timeit.timeit("func4()", setup="from __main__ import func4", number=10000000))
    print()
"""