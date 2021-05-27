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


from dqlearn import run_qdlearn


import numpy as np
import sys


def main():
    arg = sys.argv[1]
    if arg == '--qlearn':
        print("qlearn")
    elif arg == '--deepqlearn':
        print('deepqlearn')
        run_qdlearn(False)
    elif arg == '--deepqlearn-cc':
        print('deepqlearn-cc')
        run_qdlearn(True)

if __name__ == '__main__':
    main()
