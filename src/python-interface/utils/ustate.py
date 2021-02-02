""" python-interface/utils/state.py

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

UTILITY_PATH = './utils/state.so'
utility = cdll.LoadLibrary(UTILITY_PATH)

#State methods and constructors
utility.State_new.argtypes = [ctypes.c_double, ctypes.c_double,
                               ctypes.c_double, ctypes.c_double]
utility.State_new.restype = ctypes.c_void_p
utility.State_del.argtypes = [ctypes.c_void_p]
utility.State_len.argtypes = [ctypes.c_void_p]
utility.State_len.restype = ctypes.c_int
utility.State_is_equal.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
utility.State_is_equal.restype = ctypes.c_bool
utility.State_get_at.argtypes = [ctypes.c_void_p, ctypes.c_int]
utility.State_get_at.restype = ctypes.c_double
utility.State_set_at.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_double]
utility.State_copy.argtypes = [ctypes.c_void_p, ctypes.c_void_p]

#State getters
utility.State_get_pendulum_angle.argtypes = [ctypes.c_void_p]
utility.State_get_pendulum_angle.restype = ctypes.c_double
utility.State_get_motor_angle.argtypes = [ctypes.c_void_p]
utility.State_get_motor_angle.restype = ctypes.c_double
utility.State_get_pendulum_angular_velocity.argtypes = [ctypes.c_void_p]
utility.State_get_pendulum_angular_velocity.restype = ctypes.c_double
utility.State_get_motor_angular_velocity.argtypes = [ctypes.c_void_p]
utility.State_get_motor_angular_velocity.restype = ctypes.c_double

#State setters
utility.State_set_pendulum_angle.argtypes = [ctypes.c_void_p, ctypes.c_double]
utility.State_set_motor_angle.argtypes = [ctypes.c_void_p, ctypes.c_double]
utility.State_set_pendulum_angular_velocity.argtypes = [ctypes.c_void_p,
                                                        ctypes.c_double]
utility.State_set_motor_angular_velocity.argtypes = [ctypes.c_void_p,
                                                     ctypes.c_double]

class State(object):
    def __init__ (self, pendulumAngle = 0.0, motorAngle = 0.0,
                 pendulumAngularVelocity = 0.0, motorAngularVelocity = 0.0):
        self.obj = utility.State_new(pendulumAngle, motorAngle,
                 pendulumAngularVelocity, motorAngularVelocity)

    def __del__ (self):
        utility.State_del(self.obj)

    def get_at (self, index):
        return utility.State_get_at(self.obj, index)

    def set_at (self, index, value):
        utility.State_set_at(self.obj, index, value)

    def is_equal (self, state):
        return utility.State_is_equal(self.obj, state.obj)

    def len (self):
        return utility.State_len(self.obj)

    def copy (self, target):
        utility.State_copy(self.obj, target.obj)

    #State getters
    def get_pendulum_angle (self):
        return utility.State_get_pendulum_angle(self.obj)

    def get_motor_angle (self):
        return utility.State_get_motor_angle(self.obj)

    def get_pendulum_angular_velocity (self):
        return utility.State_get_pendulum_angular_velocity(self.obj);

    def get_motor_angular_velocity (self):
        return utility.State_get_motor_angular_velocity(self.obj)

    #State setters
    def set_pendulum_angle (self, angle):
        utility.State_set_pendulum_angle(self.obj, angle)

    def set_motor_angle (self, angle):
        utility.State_set_motor_angle(self.obj, angle)

    def set_pendulum_angular_velocity (self, angular_velocity):
        utility.State_set_pendulum_angular_velocity(self.obj, angular_velocity)

    def set_motor_angular_velocity (self, angular_velocity):
        utility.State_set_motor_angular_velocity(self.obj, angular_velocity)


