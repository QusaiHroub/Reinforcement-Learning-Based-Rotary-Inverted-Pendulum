""" python-interface/utils/q_table.py

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

UTILITY_PATH = './utils/q_table.so'
utility = cdll.LoadLibrary(UTILITY_PATH)


utility.QTable_new.restype = ctypes.c_void_p


utility.QTable_del.argtypes = [ctypes.c_void_p]


utility.get.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int]
utility.get.restype = ctypes.c_float


utility.set.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int, ctypes.c_float]


class QTable(object):
  def __init__ (self):
    self.obj = utility.QTable_new()


  def __del__ (self):
    utility.QTable_del(self.obj)


  def get(self, state, action):
    return utility.get(self.obj, state.obj, action)


  def set(self, state, action, qValue):
    utility.set(self.obj, state.obj, action, qValue)
