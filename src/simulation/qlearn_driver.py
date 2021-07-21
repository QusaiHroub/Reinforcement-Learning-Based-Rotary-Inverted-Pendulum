""" simulation/qlearn_driver.py

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

import Pendulum_Env
import numpy as np
import gym


from qlearn import QLearn
from utils.ustate import State


def conve_state(state):
    state = np.reshape(state, (4))
    cState = State()
    cState.set_motor_angle(state[0])
    cState.set_motor_angular_velocity(state[1])
    cState.set_pendulum_angle(state[2])
    cState.set_pendulum_angular_velocity(state[3])

    del state

    return cState


def run_qlearn():
    Alpha = 0.02
    Epsilon = 0.2
    Gamma = 0.8 #0.8 to 0.99
    epsilon_discount = 0.85
    nepisodes = 1000
    nsteps = 500
    running_step = None

    env_name = 'pendulum_env-v0'
    pendulumEnv = gym.make(env_name, lenOfTimeSeries=1)
    print("pendulum environment init done")

    qlearn = QLearn(actions=pendulumEnv.actions,
                    alpha=Alpha, gamma=Gamma, epsilon=Epsilon)
    initial_epsilon = qlearn.epsilon
    print("qlearn algorithem init done")

    #start_time = time.time()
    highest_reward = 0

    for episode in range(nepisodes):
        print("EPISODE # " + str(episode))

        pendulumEnv.reset()
        pendulumEnv.render()

        cumulated_reward = 0
        isDone = False
        cState = conve_state(pendulumEnv.getCurrentState())

        if qlearn.epsilon > 0.05:
            qlearn.epsilon *= epsilon_discount

        for step in range(nsteps):
            print("STEP # " + str(step))
            print("q-table len: ", qlearn.icount, " reuse: ", qlearn.count)

            action = qlearn.chooseAction(cState)
            print("Next action: ", action)

            obs, reward, isDone, fState = pendulumEnv.step(action)
            fState = conve_state(pendulumEnv.getCurrentState())
            pendulumEnv.render()

            cumulated_reward += reward
            if cumulated_reward > highest_reward:
                highest_reward = cumulated_reward

            qlearn.learn(cState, action, reward, fState)
            cState.copy(fState)

            if isDone:
                break
