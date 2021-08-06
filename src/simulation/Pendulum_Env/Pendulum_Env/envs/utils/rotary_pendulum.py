""" simulation/Pendulum_Env/Pendulum_Env/envs/utils/rotary_pendumum.py

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


import numpy as np
from scipy.integrate import solve_ivp
from scipy import integrate


def CreateRotaryPendulum_ODE(const_args):
    def RotaryPendulum_ODE(t, X0):
        """Rotary Pendulum ODE

        Parameters
        ----------

        t: double
            time
        X0: array
            current state

        Returns
        -------

            [motor angle, motor angular velocity, pendulum angle, pendulum angular velocity]
        """

        tau, I, m, l, Rl, g = const_args
        Y1, Y2, Y3, Y4 = X0

        t4 = Y3
        t2 = np.sin(t4)
        t3 = Rl ** 2
        t5 = np.cos(t4)
        t6 = Y4
        t7 = t5 ** 2
        t8 = Y2
        t9 = l ** 2
        t10 = I * 1.2e1
        t11 = m * t3 * 1.2e1
        t12 = t2 ** 2
        t13 = m * t9 * t12 * 4.0
        t14 = (t10 + t11 + t13) - (m * t3 * t7 * 9.0)
        t15 = 1.0 / t14
        t16 = t8 ** 2
        t17 = t6 ** 2
        c1 = t15 * (tau * 1.2e1 + Rl * g * m * t2 * t5 * 9.0 - Rl * l * m * t2 * t17 * 6.0 - m * t2 * t5 * t6 * t8 * t9 * 8.0 + Rl * l * m * t2 * t7 * t16 * 6.0)
        c2 = (t15 * (I * g * t2 * 1.8e1 + Rl * t5 * tau * 1.8e1 + g * m * t2 * t3 * 1.8e1 + I * l * t2 * t5 * t16 * 1.2e1 + g * m * t2 * t9 * t12 * 6.0 + l * m * t2 * t3 * t5 * t16 * 1.2e1 - l * m * t2 * t3 * t5 * t17 * 9.0 - Rl * m * t2 * t6 * t7 * t8 * t9 * 1.2e1 + l * m * t2 * t5 * t9 * t12 * t16 * 4.0)) / l

        dYdT = [t8, c1, t6, c2]
        return dYdT

    return RotaryPendulum_ODE


def solveRL(X0, t, I, m, l, R, g, tau):

    const_args = [tau, I, m, l, R, g]
    RotaryPendulum_ODE = CreateRotaryPendulum_ODE(const_args)

    t0 = 0
    t_val = np.linspace(t0, t, 2)
    y = np.zeros((len(t_val), len(X0)))
    y[0, :] = X0
    r = integrate.ode(RotaryPendulum_ODE).set_integrator("dopri5", nsteps=1000)
    r.set_initial_value(X0, t0)
    for i in range(1, t_val.size):
        y[i] = r.integrate(t_val[i])

    ylast = len(y) - 1
    return y[ylast]
