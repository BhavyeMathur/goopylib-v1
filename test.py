import timeit
import math
import os

from matplotlib import pyplot as plt

from goopylib.c_colours import *
from goopylib.math.bezier_curve import *

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


# countlines("goopylib")

combination(2, 5)

c = ColourRGB(255, 0, 0)
print("RGB:", c + 10)

c1 = ColourHex("#ff00aa")
print("Hex:", c1)

print(c + c1 + 17)

#c2 = ColourCMYK(100, 0, 100, 0)
#print("CMYK:", c2)

#c3 = ColourHSL(100, 0, 50)
#print("HSL:", c3)

#c4 = ColourHSV(100, 30, 50)
#print("HSV:", c4)

"""
while True:
    print(timeit.timeit("func1()", setup="from __main__ import func1", number=10000000))
    print(timeit.timeit("func2()", setup="from __main__ import func2", number=10000000))
    print(timeit.timeit("func3()", setup="from __main__ import func3", number=10000000))
    print(timeit.timeit("func4()", setup="from __main__ import func4", number=10000000))
    print()
"""
