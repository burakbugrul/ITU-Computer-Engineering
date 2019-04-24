"""
    Author: Muhammed Burak Bugrul
    Student ID: 150140015
"""

import sys
import matplotlib.pyplot as plt

def standard_deviation(x):
    mean = sum(x) / len(x)
    return (sum([((item - mean) ** 2) for item in x]) / len(x)) ** 0.5

def draw(x, y, color, column):
    markerline, stemlines, baseline = column.stem(x, y, '-')
    plt.setp(baseline, 'color', color, 'linewidth', 0)
    plt.setp(stemlines, 'color', color)

def standard_normalize(x):

    mean = sum(x) / len(x)
    S = standard_deviation(x)

    return [(item - mean) / S for item in x]

inputs = map(int, sys.argv[1:])

begin_x, end_x, begin_y, end_y = map(int, sys.argv[1:5])

x_interval = [i for i in range(begin_x, end_x + 1)]
y_interval = [i for i in range(begin_y, end_y + 1)]

x = list(map(int, sys.argv[5 : 5 + (end_x - begin_x + 1)]))
y = list(map(int, sys.argv[5 + (end_x - begin_x + 1) : ]))

x = standard_normalize(x)
y = standard_normalize(y)

fig, ax = plt.subplots(nrows=1, ncols=2)
col1, col2 = ax

draw(x_interval, x, 'r', col1)
draw(y_interval, y, 'y', col2)

plt.show()