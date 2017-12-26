#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Yee_172'
__date__ = '2017/12/22'


import sys
import random
from time import sleep


PATH = sys.path[0]
N = 250000000
INTERVAL = 1000000
REST_TIME = 30
VARIA = (
         'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
         'abcdefghijklmnopqrstuvwxyz'
         '`~!@#$%^&*()_+-=,./<>?;:"[]{}\|'
        )


def wrong_data():
    n = random.randint(3, 15)
    m = random.choice([0, 0, 0, 0, 0, 1, 2, 3, 4, 5])
    result = []
    for _ in range(n):
        result.append(random.choice(VARIA))
    for _ in range(m):
        result.append(random.choice('0123456789'))
    random.shuffle(result)
    return ''.join(result)


with open(PATH + '/massive_float/test2.txt', 'w') as f:
    for _ in range(N):
        dice = random.choice([0] * 999 + [1])
        if dice is 1:
            f.write(wrong_data() + '\n')
        # Inject dirty data without decreasing the number of supposed data
        # 0.1% possibility go wrong

        radius = random.randint(-100, 100)
        maximum = float('1E%d' % radius)
        minimum = -maximum
        f.write(str(random.uniform(minimum, maximum)) + '\n')
        # Get random float in random range

        sys.stdout.write('%011.8f' % ((_ + 1) * 100 / N) + '%\r')
        sys.stdout.flush()
        # Show the progress in percentage form
        if (_ + 1) % INTERVAL is 0 and INTERVAL is not N:
            for __ in range(REST_TIME, 0, -1):
                sys.stdout.write('Rest at %011.8f' % ((_ + 1) * 100 / N) + '%' + ' -- remain %02d seconds\r' % __)
                sys.stdout.flush()
                sleep(1)
            # This program will consume a lot of computation source,
            # which will lead to the temperature of the core going higher,
            # let computer cool down for a while after a bunch of work
            sys.stdout.write(''.center(50) + '\r')
            sys.stdout.flush()
