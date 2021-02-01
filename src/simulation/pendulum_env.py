""" simulation/pendulum_env.py

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

import gym
import numpy as np

from gym import spaces
from gym.utils import seeding

from utils.state import State

class PendulumEnv(gym.Env):
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 30
    }

    def __init__(self, g=9.8):
        self.max_speed = 8
        self.max_torque = 2.0
        self.l = 1.0
        self.r = 1.0
        self.g = g
        self.m_rod = 0.15
        self.m_arm = 0.2
        self.c_rod = 1.0
        self.c_arm = 1.0
        self.delay = 0.1
        self.viewer = None
        self.state = State()

        high = np.array([1., 1., self.max_speed], dtype=np.float64)
        #TODO: rewrite spaces.Box
        self.action_space = spaces.Box(
            low = -self.max_torque,
            high = self.max_torque,
            shape = (1, ),
            dtype = np.float64
        )
        self.observation_space = spaces.Box(
            low = -high,
            high = high,
            dtype = np.float64
        )

        self.seed()

    def seed(self, seed=None):
        self.np_random, seed = seeding.np_random(seed)
        return [seed]

    def step(self, tau=0.0):
        theta = self.state.get_motor_angle()
        dtheta = self.state.get_motor_angular_velocity()
        alpha = self.state.get_pendulum_angle()
        dalpha = self.state.get_pendulum_angular_velocity()

        l = self.l
        r = self.r
        g = self.g
        m_rod = self.m_rod
        m_arm = self.m_arm
        c_rod = self.c_rod
        c_arm = self.c_arm
        delay = self.delay

        tau = np.clip(tau, -self.max_torque, self.max_torque)[0]

        #TODO:
        costs =

        newtheta =
        newdtheta =

        newalpha =
        newdalpha =

        self.state.set_motor_angle(newtheta)
        self.state.set_motor_angular_velocity(newdtheta)
        self.state.set_pendulum_angle(newalpha)
        self.state.set_pendulum_angular_velocity(newdalpha)

        return self._get_obs(), -costs, False, {}

    def reset(self):
        high = np.array([np.pi, 1, np.pi, 1])
        theta, dtheta, alpha, dalpha = self.np_random.uniform(low =- high, high = high)

        self.state.set_motor_angle(theta)
        self.state.set_motor_angular_velocity(dtheta)
        self.state.set_pendulum_angle(alpha)
        self.state.set_pendulum_angular_velocity(dalpha)

        return self._get_obs()

    def _get_obs(self):
        theta = self.state.get_motor_angle()
        dtheta = self.state.get_motor_angular_velocity()
        alpha = self.state.get_pendulum_angle()
        dalpha = self.state.get_pendulum_angular_velocity()

        return np.array([np.cos(theta), np.sin(theta), dtheta, np.cos(alpha),
                         np.sin(alpha), dalpha])

    def render(self, mode='human'):
        if self.viewer is None:
            from gym.envs.classic_control import rendering
            self.viewer = rendering.Viewer(500, 500)
            self.viewer.set_bounds(-2.2, 2.2, -2.2, 2.2)

            rod = rendering.make_capsule(1, .2)
            rod.set_color(.3, .3, .3)
            self.rod_transform = rendering.Transform()
            rod.add_attr(self.rod_transform)
            self.viewer.add_geom(rod)

            axle = rendering.make_circle(.05)
            axle.set_color(0, 0, 0)
            self.viewer.add_geom(axle)

        self.rod_transform.set_rotation(self.state.get_pendulum_angle() \
                                         + np.pi / 2)

        return self.viewer.render(return_rgb_array=mode == 'rgb_array')

    def close(self):
        if self.viewer:
            self.viewer.close()
            self.viewer = None
            del self.state
            self.state = None
