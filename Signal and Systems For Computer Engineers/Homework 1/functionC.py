"""
    Author: Muhammed Burak Bugrul
    Student ID: 150140015
"""

import sys
import matplotlib.pyplot as plt

def convolution(a, b):

    result = [0]*(len(a)+len(b)-1)

    for i in range(len(result)):
        for j in range(max(0, i-len(b)+1), min(i+1, len(a))):
            result[i] += a[j]*b[i-j]
    
    return result

def draw(x, y, color):
    markerline, stemlines, baseline = plt.stem(x, y, '-')
    plt.setp(baseline, 'color', color, 'linewidth', 0)
    plt.setp(stemlines, 'color', color)


inputs = map(int, sys.argv[1:])

begin_x, end_x, begin_y, end_y = map(int, sys.argv[1:5])

x_interval = [i for i in range(begin_x, end_x + 1)]
y_interval = [i for i in range(begin_y, end_y + 1)]

x = list(map(int, sys.argv[5 : 5 + (end_x - begin_x + 1)]))
y = list(map(int, sys.argv[5 + (end_x - begin_x + 1) : ]))

print(convolution(x, y))
