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

class PendulumEnv(gym.Env):
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 30
    }


    def __init__(self, g=9.8, lenOfTimeSeries=10):
        #motor max speed 11000rpm = 366.67PI rad/s, avg speed 549rpm = 57.5 rad/s
        self.max_speed = 200
        self.max_torque = 0.1 #N.m
        self.l = 183.2e-3 #0.153 #m
        self.r = 109e-3 # 0.172
        self.g = g
        self.m_rod = 3.3e-3 #0.14 #kg
        self.m_arm_encoder = 20.3e-3 #0.18
        self.m_encoder = 0.012 #0.04
        self.m_re = 0.02 #0.01
        self.viewer = None
        self.state = np.array([[]])
        self.stepSize = 0.006
        self.alpha_threshold_radians = 0.122
        self.count = 0
        self.done = 1
        self.lenOfTimeSeries = lenOfTimeSeries
        self.reward = np.array([])

        high = np.array([[np.pi, self.max_speed, np.pi, self.max_speed] * lenOfTimeSeries], dtype=np.float64)
        high = np.reshape(high, (lenOfTimeSeries, 4, 1))
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
        cState = np.reshape(cState, (4))
        oldState = np.reshape(oldState, (4))
        result = 0.0
        #TODO
        if (np.abs(cState[2]) <= self.alpha_threshold_radians):
            result = 100.
        if np.abs(cState[2]) < np.abs(oldState[2]):
            result = 40.
        else:
            result = -10.

        return result


    def norm(self, theta, dtheta, alpha, dalpha):
        itheta = angle_normalize(theta)
        idtheta = dtheta
        ialpha = angle_normalize(alpha)
        idalpha = dalpha
        return [itheta, idtheta, ialpha, dalpha]


    def step(self, action):
        lenOfTimeSeries = self.lenOfTimeSeries
        pwm = self.actions[action]

        newtheta, newdtheta, newalpha, newdalpha = 
        newdtheta = np.clip(newdtheta, -self.max_speed, self.max_speed)
        newdalpha = np.clip(newdalpha, -self.max_speed, self.max_speed)

        state = np.delete(state, [0, 1, 2, 3])
        state = np.append(state, self.norm(newtheta, newdtheta, newalpha, newdalpha))
        state = np.reshape(state, (lenOfTimeSeries, 4, 1))
        reward = self.reinforcenmentSignal(state[lenOfTimeSeries - 1], self.state[lenOfTimeSeries - 1])
        self.state = state
        self.reward = np.delete(self.reward, 0)
        self.reward = np.append(self.reward, reward)
        reward = sum(self.reward)

        if np.abs(newalpha) < self.alpha_threshold_radians:
            self.count += 1
        else:
            self.count = 0


        done = bool(
             np.abs(newalpha) <= self.alpha_threshold_radians
        )

        return self.getCurrentState(), reward, done, {}


    def reset(self):
        lenOfTimeSeries = self.lenOfTimeSeries
        high = np.array([np.pi, 1, np.pi, 1])
        theta, dtheta, alpha, dalpha = self.np_random.uniform(low =- high, high = high)

        self.state = np.array(self.norm(theta, dtheta, alpha, dalpha) * lenOfTimeSeries)
        self.state = np.reshape(self.state, (lenOfTimeSeries, 4, 1))
        self.reward = np.array([0] * lenOfTimeSeries)

        return self.getCurrentState()


    def _get_obs(self):
        theta, dtheta, alpha, dalpha = self.state

        return np.array([np.cos(theta), np.sin(theta), dtheta, np.cos(alpha),
                         np.sin(alpha), dalpha])


    def render(self, mode='human'):
        lenOfTimeSeries = self.lenOfTimeSeries
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

        self.rod_transform.set_rotation(-float(self.state[lenOfTimeSeries - 1][2]) \
                                         + np.pi / 2)

        return self.viewer.render(return_rgb_array=mode == 'rgb_array')


    def close(self):
        if self.viewer:
            self.viewer.close()
            self.viewer = None
            self.state = None


    def getCurrentState(self):
        if self.lenOfTimeSeries == 1:
            return np.reshape(self.state, (self.lenOfTimeSeries, 4, 1))
        return np.array(self.state)
