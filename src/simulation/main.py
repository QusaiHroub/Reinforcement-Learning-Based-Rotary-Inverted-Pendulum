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


def main():
    arg = sys.argv[1]
    if arg == '--qlearn':
        print("qlearn")
        run_qlearn()
    elif arg == '--deepqlearn':
        print('deepqlearn')
        run_dqlearn(False)
    elif arg == '--deepqlearn-cc':
        print('deepqlearn-cc')
        run_dqlearn(True)
    elif arg == '-h' or arg == '--help':
        print('Usage: python3 main.py [option]\n')
        print('List of options:')
        print('--qlearn             run q-learn reinforcement learing ')
        print('--deepqlearn         run deep q-learn reinforcement learning (Dense layers)')
        print('--deepqlearn-cc      run deep q-learn reinforcement learning (Convilution layers)')


if __name__ == '__main__':
    main()
