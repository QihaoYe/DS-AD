#!/usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Yee_172'
__date__ = '2017/11/17'


import sys
from random import randint


MODE = 'ADDITION'
SEPARATOR = ' '
NUMBER = 100000
PATH = sys.path[0] + '/source.txt'
HEAD = [130, 131, 132, 141, 143, 145, 155, 156, 185, 186, 133, 142, 144, 
        146, 148, 149, 153, 180, 181, 189, 134, 135, 136, 137, 138, 139, 
        140, 147, 150, 151, 152, 157, 158, 159, 182, 183, 187, 188]
HEAD_LENGTH = len(HEAD)


# LianTong + WangTong --> [130-132, 141, 143, 145, 155, 156, 185, 186]
# Dianxin  + WeiTong  --> [133, 142, 144, 146, 148, 149, 153, 180, 181, 189]
# YiDong   + TieTong  --> [134-140, 147, 150-152, 157-159, 182, 183, 187, 188]
# Total --> [130, 131, 132, 141, 143, 145, 155, 156, 185, 186, 133, 142, 144, 
#            146, 148, 149, 153, 180, 181, 189, 134, 135, 136, 137, 138, 139, 
#            140, 147, 150, 151, 152, 157, 158, 159, 182, 183, 187, 188]


store = []
length = 0
with open(PATH, 'a+' if MODE is 'ADDITION' else 'w') as f:
    for i in range(NUMBER):
        if i < NUMBER / 2:
            temp = str(HEAD[randint(0, HEAD_LENGTH - 1)]) + '%04d' % randint(0, 9999) + '%04d' % randint(0, 9999)
            store.append(temp)
            length += 1
            f.write(temp + SEPARATOR)
        else:
            temp = store[randint(0, length - 1)]
            f.write(temp + SEPARATOR)
        # Generate repeat valid phone numbers
        sys.stdout.write('%08.5f' % ((i + 1) * 100 / NUMBER) + '%\r')
        sys.stdout.flush()

