#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Yee_172'
__date__ = '2017/12/17'


import sys
from random import randint
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator


PATH = sys.path[0]
BOUNDARY = 50
N = 300
result = [[0, 0]]


def write_in(info, directory=PATH, filename='output', extension='.txt', mode='w'):
    with open(directory + '/' + filename + extension, mode) as f:
        f.write(info)


def sprinkle(boundary=BOUNDARY):
    x, y = [0, 0]
    while 1:
        if [x, y] not in result:
            result.append([x, y])
            break
        else:
            x, y = [randint(-BOUNDARY, BOUNDARY), randint(-BOUNDARY, BOUNDARY)]


def store(result, filename='points'):
    string = ''
    for each in result[1:]:
        string += '%03d %03d\n' % (each[0], each[1])
    write_in(string, filename=filename)


for _ in range(N):
    sprinkle()


store(result)


xmajorLocator = MultipleLocator(10)
ymajorLocator = MultipleLocator(10)
plt.title('Positions of Crocodiles')
plt.xlabel('x axis')
plt.ylabel('y axis')
ax = plt.subplot(111)
ax.xaxis.set_major_locator(xmajorLocator)
ax.yaxis.set_major_locator(ymajorLocator)
plt.axis([-BOUNDARY, BOUNDARY, -BOUNDARY, BOUNDARY])
plt.scatter([each[0] for each in result], [each[1] for each in result], color='red', marker='o', label='Crocodiles')
plt.scatter(0, 0, color='blue', marker='o', label='007')
plt.text(-2.3, -3, '007')
ax.xaxis.grid(True, which='major')
ax.yaxis.grid(True, which='major')
fig = plt.gcf()
fig.set_size_inches(8, 8)
fig.savefig(PATH + '/points.png', dpi=100)
