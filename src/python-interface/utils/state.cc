/* python-interface/utils/PState.cc
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

#include "../../utils/pstate.hh"
#include "../../utils/type.hh"

extern "C" {
    PState* State_new(float_32b pendulumAngle, float_32b motorAngle,
           float_32b pendulumAngularVelocity, float_32b motorAngularVelocity) {
        return new PState(pendulumAngle, pendulumAngularVelocity, motorAngle,
                         motorAngularVelocity);
    }
    void State_del(PState* self) {
        delete self;
    }

    float_32b State_get_at(PState* self, int index) {
        return (*self).unBoxAt(index);
    }

    void State_set_at(PState* self, int index, float_32b value) {
        (*self).setAt(index, value);
    }

    bool State_is_equal(PState* self, PState* PState) {
        return (*self) == (*PState);
    }

    unsigned short State_len (PState* self) {
        return self->size();
    }

    void State_copy (PState* self, PState* target) {
        (*self) = (*target);
    }

    //State getters
    float_32b State_get_pendulum_angle (PState* self) {
        return self->getPendulumAngle();
    }
    float_32b State_get_motor_angle (PState* self) {
        return self->getMotorAngle();
    }
    float_32b State_get_pendulum_angular_velocity (PState* self) {
        return self->getPendulumAngularVelocity();
    }
    float_32b State_get_motor_angular_velocity (PState* self) {
        return self->getMotorAngularVelocity();
    }

    //PState setters
    void State_set_pendulum_angle (PState* self, float_32b pendulum_angle) {
        self->setPendulumAngle(pendulum_angle);
    }
    void State_set_motor_angle (PState* self, float_32b motor_angle) {
        self->setMotorAngle(motor_angle);
    }
    void State_set_pendulum_angular_velocity (PState* self,
        float_32b pendulum_angular_velocity) {
        self->setPendulumAngularVelocity(pendulum_angular_velocity);
    }
    void State_set_motor_angular_velocity (PState* self,
        float_32b motor_angular_velocity) {
        self->setMotorAngularVelocity(motor_angular_velocity);
    }
}