""" python-interface/utils/math.py

 This file is part of Reinforcement Learning-based Rotary Inverted Pendulum
 Graduation Project.

 Authors:
 Qusai Hroub <qusaihroub.r@gmail.com>

 This program is free software; you can redistribute it and/or modify it
 under the terms and conditions of the GNU General Public License,
 version 3, as published by the Free Software Foundation.

 This program is distributed in the hope it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 more details.
"""

import ctypes
from ctypes import cdll

UTILITY_PATH = './utils/math.so'
utility = cdll.LoadLibrary(UTILITY_PATH)

utility.angle_normalize.argtypes = [ctypes.c_double]
utility.angle_normalize.restype = ctypes.c_double

def angle_normalize (angle):
    return utility.angle_normalize(angle)
