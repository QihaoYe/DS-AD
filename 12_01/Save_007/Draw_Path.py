#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Yee_172'
__date__ = '2017/12/17'


import sys
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator


BOUNDARY_X = 50
BOUNDARY_Y = 50
PATH = sys.path[0]
points = [[0, 0]]
path = []


def final_step(path):
    if path:
        x, y = path[-1]
        dir_x0 = BOUNDARY_X - x
        if dir_x0 <= 5:
            path.append([BOUNDARY_X, y])
            return
        dir_x1 = x + BOUNDARY_X
        if dir_x1 <= 5:
            path.append([-BOUNDARY_X, y])
            return
        dir_y0 = BOUNDARY_Y - y
        if dir_y0 <= 5:
            path.append([x, BOUNDARY_Y])
            return
        dir_y1 = y + BOUNDARY_Y
        if dir_y1 <= 5:
            path.append([x, -BOUNDARY_Y])
            return
    else:
        print('There exists no possible way out!!!')


with open(PATH + '/points.txt', 'r') as f:
    readin = f.read().split('\n')[:-1]
    for point in readin:
        points.append([int(each) for each in point.split(' ')])


with open(PATH + '/path.txt', 'r') as f:
    readin = f.read().split('\n')[:-1]
    for point in readin:
        path.append([int(each) for each in point.split(' ')])


final_step(path)
steps = len(path) - 1


xmajorLocator = MultipleLocator(10)
ymajorLocator = MultipleLocator(10)
plt.title('One of the Possible Way Out')
plt.xlabel('x axis')
plt.ylabel('y axis')
ax = plt.subplot(111)
ax.xaxis.set_major_locator(xmajorLocator)
ax.yaxis.set_major_locator(ymajorLocator)
plt.axis([-BOUNDARY_X, BOUNDARY_X, -BOUNDARY_Y, BOUNDARY_Y])
plt.scatter([each[0] for each in points], [each[1] for each in points], color='red', marker='o', label='Crocodiles')
for _ in range(steps):
    plt.plot([path[ _][0], path[_ + 1][0]], [path[_][1], path[_ + 1][1]], color='green')
plt.scatter(0, 0, color='blue', marker='o', label='007')
plt.text(-2.3, -3, '007')
ax.xaxis.grid(True, which='major')
ax.yaxis.grid(True, which='major')
fig = plt.gcf()
fig.set_size_inches(BOUNDARY_X * 0.16, BOUNDARY_Y * 0.16)
fig.savefig(PATH + '/points_with_path.png', dpi=100)
