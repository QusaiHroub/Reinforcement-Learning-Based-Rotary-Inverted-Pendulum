""" simulation/qlearn.py

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

import random

from utils.ustate import State
from utils.qtable import QTable

class QLearn:
    def __init__(self, actions, epsilon, alpha, gamma):
        self.qtable = QTable()
        self.epsilon = epsilon
        self.alpha = alpha
        self.gamma = gamma
        self.actions = actions
        self.count = 0
        self.icount = 0


    def getQ(self, state, action, default=None):
        """get q-value

        Parameters
        ----------

        state: state
            target state
        action: double
            target action
        default: double
            the value that returns when the key is not found

        Returns
        -------

            A list of q-values for a specific action at spectific state
        """

        result = self.qtable.get(state, int(action))

        if (abs(result - 1e9) < 0.0001):
            return default

        return result


    def getQListForState(self, state):
        """get list of q-values

        Parameters
        ----------

        state: state
            target state

        Returns
        -------

            A list of q-values for a specific state
        """

        return [self.getQ(state, action, 0.0) for action in self.actions]


    def learnQ(self, state, action, reward, dfreward):
        """calculat the new q-value.

        Parameters
        ----------

        state: state
            old state
        action: double
            performed action
        reward: double
            reinforcenment signal
        dfreward: double
            discounted future reward
        """

        print (str(state))
        oldq = self.getQ(state, int(action))
        print(oldq)
        if oldq is None:
            print('insert')
            self.icount += 1
            self.qtable.set(state, int(action), reward)
        else:
            print('update')
            self.count += 1
            self.qtable.set(state, int(action), oldq + self.alpha * (dfreward - oldq))


    def policyFunction(self, state):
        """epsilon-greedy policy

        Parameters
        ----------

        state: State
            current state

        Returns
        -------

        qlist: double
            list of q-values
        maxQ: double
            max q-value in qlist
        """

        qlist = self.getQListForState(state)
        maxQ = max(qlist)

        return qlist, maxQ


    def chooseAction(self, state):
        """choose an action to be performed.

        Parameters
        ----------

        state: state
            current state

        Returns
        -------

        selected action
        """

        if random.random() < self.epsilon:
            return random.randint(0, len(self.actions) - 1)

        qlist, maxQ = self.policyFunction(state)

        count = qlist.count(maxQ)
        if count == 1:
            return qlist.index(maxQ)

        maxQsIters = [it for it in range(len(self.actions)) if qlist[it] == maxQ]
        selectedIter = random.choice(maxQsIters)

        return selectedIter


    def learn(self, state, action, reward, fState):
        """learn.

        Parameters
        ----------

        state: State
            current state
        action: double
            selected action
        reward: double
            reinforcenment signal
        fState: state
            future state (i.e. new state)
        """

        maxq = max(self.getQListForState(fState))

        #discounted future reward
        dfreward = reward + self.gamma * maxq
        newState = State()
        newState.copy(state)
        self.learnQ(newState, action, reward, dfreward)

