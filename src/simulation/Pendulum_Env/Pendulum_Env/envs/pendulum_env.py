""" simulation/Pendulum_Env/Pendulum_Env/envs/pendulum_env.py

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


from .utils.pmath import angle_normalize
from .utils.rotary_pendulum import solveRL


class PendulumEnv(gym.Env):
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 30
    }


    def __init__(self, g=9.8):
        #motor max speed 11000rpm = 366.67PI rad/s, avg speed 549rpm = 57.5 rad/s
        self.max_speed = 200
        self.max_torque = 1 #N.m
        self.l = 135e-3
        self.r = 156e-3
        self.g = g
        self.m_rod = 0.14 #kg
        self.m_arm_encoder = 0.18
        self.m_encoder = 0.04
        self.m_re = 0.02
        self.viewer = None
        self.state = np.array([[]])
        self.stepSize = 0.006
        self.alpha_threshold_radians = 0.122
        self.alpha_threshold_radians_2 = np.pi / 2
        self.count = 0
        self.done = 1
        self.reward = np.array([])

        high = np.array([np.pi, self.max_speed, np.pi, self.max_speed], dtype=np.float64)

        self.observation_space = spaces.Box(
            low = -high,
            high = high,
            dtype = np.float64
        )

        self.actions = [0.6, -0.6, 0.0]
        self.action_space = spaces.Discrete(len(self.actions))

        self.seed()


    def seed(self, seed=None):
        self.np_random, seed = seeding.np_random(seed)
        return [seed]


    def reinforcenmentSignal(self, cState, oldState):
        result = 0.0

        if np.abs(cState[2]) <= self.alpha_threshold_radians:
            result = 15.
        elif np.abs(cState[2]) <= self.alpha_threshold_radians_2:
            result = ((np.pi / 2 - np.abs(cState[2])) * 2 / np.pi) * 10
        else:
            result = -100.

        return result


    def norm(self, theta, dtheta, alpha, dalpha):
        itheta = angle_normalize(theta)
        idtheta = dtheta
        ialpha = angle_normalize(alpha)
        idalpha = dalpha
        return [itheta, idtheta, ialpha, dalpha]


    def step(self, action):
        state = self.state
        l = self.l
        r = self.r
        g = self.g
        m_rod = self.m_rod
        m_arm_encoder = self.m_arm_encoder
        m_encoder = self.m_encoder
        m_arm = m_arm_encoder - m_encoder
        stepSize = self.stepSize
        m_re = self.m_re
        Ino_e = m_arm * r ** 2 / 3
        Itot = Ino_e + m_encoder * m_re ** 2
        I = Itot
        tau = self.actions[action] * self.max_torque

        stateForSolver = state
        newtheta, newdtheta, newalpha, newdalpha = solveRL(stateForSolver, stepSize, I, m_rod, l, r, g, tau)
        newdtheta = np.clip(newdtheta, -self.max_speed, self.max_speed)
        newdalpha = np.clip(newdalpha, -self.max_speed, self.max_speed)

        state = self.norm(newtheta, newdtheta, newalpha, newdalpha)
        reward = self.reinforcenmentSignal(state, self.state)

        done = reward == -100

        self.state = state

        if np.abs(newalpha) < self.alpha_threshold_radians:
            self.count += 1
        else:
            self.count = 0

        return self.getCurrentState(), reward, done, {}


    def reset(self, init_state = None):
        high = np.array([np.pi, 10, 0.6, 10])
        theta, dtheta, alpha, dalpha = self.np_random.uniform(low =- high, high = high)

        #theta, dtheta, alpha, dalpha = (0, 0, 0.6, 5)

        self.state = np.array(self.norm(theta, dtheta, alpha, dalpha))

        return self.getCurrentState()


    def _get_obs(self):
        theta, dtheta, alpha, dalpha = self.state

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

        self.rod_transform.set_rotation(-float(self.state[2]) \
                                         + np.pi / 2)

        return self.viewer.render(return_rgb_array=mode == 'rgb_array')


    def close(self):
        if self.viewer:
            self.viewer.close()
            self.viewer = None
            self.state = None


    def getCurrentState(self):
        return np.array(self.state)
