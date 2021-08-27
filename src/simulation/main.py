""" simulation/main.py

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


from dqlearn import run_dqlearn
from qlearn_driver import run_qlearn


import numpy as np
import sys

def help():
    print('Number of options must be grater than zero')
    print('Usage: python3 main.py [option]\n')
    print('List of options:')
    print('--qlearn                                  run q-learn reinforcement learing ')
    print('--deepqlearn                              run deep q-learn reinforcement learning (Dense layers)')
    print('--deepqlearn-cc                           run deep q-learn reinforcement learning (Convilution layers)')
    print('--continue ${number of new episodes}      continue training from last checkpoint (used only with --deepqlearn and --deepqlearn-cc)')
    print('--load                                    load the latest policy (used only with --deepqlearn and --deepqlearn-cc)')
    print('--train                                   start train from scratch')



def setParams (argv):
    checkpointer_restor = False
    load_tf_policy = False
    continueTrainEpisodes = 10

    if len(argv) >= 3:
        if argv[2] == '--continue':
            checkpointer_restor = True
        elif argv[2] == '--load':
            load_tf_policy = True

    if len(argv) >= 4:
        if checkpointer_restor:
            continueTrainEpisodes = int(argv[3])

    return checkpointer_restor, load_tf_policy, continueTrainEpisodes


def main():
    if len(sys.argv) < 2:
        help()
    arg = sys.argv[1]
    if arg == '--qlearn':
        print("qlearn")
        run_qlearn()
    elif arg == '--deepqlearn':
        print('deepqlearn')
        checkpointer_restor, load_tf_policy, continueTrainEpisodes = setParams(sys.argv)
        run_dqlearn(False, checkpointer_restor, load_tf_policy, continueTrainEpisodes)
    elif arg == '--deepqlearn-cc':
        print('deepqlearn-cc')
        checkpointer_restor, load_tf_policy, continueTrainEpisodes = setParams(sys.argv)
        run_dqlearn(True, checkpointer_restor, load_tf_policy, continueTrainEpisodes)
    elif arg == '-h' or arg == '--help':
        help()


if __name__ == '__main__':
    main()
