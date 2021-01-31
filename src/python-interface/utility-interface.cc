/* python/utility-interface.cc
 *
 * This file is part of Reinforcement Learning-based Rotary Inverted Pendulum
 * Graduation Project.
 *
 * Authors:
 * Qusai Hroub <qusaihroub.r@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

module;

import utility;

export module utilityInterface;

export extern "C" {
    State* State_new(double pendulumAngle, double motorAngle,
           double pendulumAngularVelocity, double motorAngularVelocity) {
        return new State(pendulumAngle, pendulumAngularVelocity, motorAngle,
                         motorAngularVelocity);
    }
    void State_del(State *self) {
        delete self;
    }

    double State_get_at(State *self, int index) {
        return (*self)[index];
    }

    void State_set_at(State *self, int index, double value) {
        (*self)[index] = value;
    }

    bool State_is_equal(State *self, State *state) {
        return (*self) == (*state);
    }

    unsigned short State_len (State *self) {
        return self->size();
    }

    //State getters
    double State_get_pendulum_angle (State *self) {
        return self->getPendulumAngle();
    }
    double State_get_motor_angle (State *self) {
        return self->getMotorAngle();
    }
    double State_get_pendulum_angular_velocity (State *self) {
        return self->getPendulumAngularVelocity();
    }
    double State_get_motor_angular_velocity (State *self) {
        return self->getMotorAngularVelocity();
    }

    //State setters
    void State_set_pendulum_angle (State *self, double pendulum_angle) {
        self->setPendulumAngle(pendulum_angle);
    }
    void State_set_motor_angle (State *self, double motor_angle) {
        self->setMotorAngle(motor_angle);
    }
    void State_set_pendulum_angular_velocity (State *self,
        double pendulum_angular_velocity) {
        self->setPendulumAngularVelocity(pendulum_angular_velocity);
    }
    void State_set_motor_angular_velocity (State *self,
        double motor_angular_velocity) {
        self->setMotorAngularVelocity(motor_angular_velocity);
    }

    double angle_normalize (double angle) {
        return angleNormalize(angle);
    }
}

