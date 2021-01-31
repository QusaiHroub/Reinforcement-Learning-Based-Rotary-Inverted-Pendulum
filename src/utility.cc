/* utility.cc
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

#include <math.h>

export module utility;

export const double PI = 3.142;

export double angleNormalize(double angle);

export class State {
private:
    const unsigned short SIZE = 4;

    //All these values are in radians.
    double mPendulumAngle,
           mMotorAngle,
           mPendulumAngularVelocity,
           mMotorAngularVelocity;

public:
    State (double pendulumAngle = 0.0, double pendulumAngularVelocity = 0.0,
           double motorAngle = 0.0, double motorAngularVelocity = 0.0)
            : mPendulumAngle(pendulumAngle), mMotorAngle(motorAngle),
           mPendulumAngularVelocity(pendulumAngularVelocity),
           mMotorAngularVelocity(motorAngularVelocity) {}

    //Getters
    double getPendulumAngle () {
        return mPendulumAngle;
    }
    double getMotorAngle () {
        return mMotorAngle;
    }
    double getPendulumAngularVelocity () {
        return mPendulumAngularVelocity;
    }
    double getMotorAngularVelocity () {
        return mMotorAngularVelocity;
    }

    /**
     * size
     *
     * @return const unsigned short - represent the number of data members
     */
    unsigned short size() const {
        return SIZE;
    }

    //Setters
    void setPendulumAngle (double pendulumAngle) {
        mPendulumAngle = angleNormalize(pendulumAngle);
    }
    void setMotorAngle (double motorAngle) {
        mMotorAngle = angleNormalize(motorAngle);
    }
    void setPendulumAngularVelocity (double pendulumAngularVelocity) {
        mPendulumAngularVelocity = pendulumAngularVelocity;
    }
    void setMotorAngularVelocity (double motorAngularVelocity) {
        mMotorAngularVelocity = motorAngularVelocity;
    }

    /**
     * intexing the data member of the state
     *
     * @tparam index is of the {int} type
     * @param index - index of the data member
     *
     * @throws Index out of range when the index is more than or equal to
     * the size
     *
     * @return double - the value of data member at that index
     */
    double &operator[] (unsigned int index) {
        if (index >= SIZE) {
            throw "Index out of range";
        }

        switch (index) {
            case 0: return mPendulumAngle;
            case 1: return mPendulumAngularVelocity;
            case 2: return mMotorAngle;
        }

        return mMotorAngularVelocity;
    }

    /**
     * compare two states
     *
     * @tparam state is of the {State &} type
     * @param state - the second state to compare with it
     *
     * @return bool - true if the two states are the same
     */
    bool operator== (State &state) {
        bool result = true;

        for (int i = 0; i < SIZE; i++) {
            result = result && ((*this)[i] == state[i]);
        }

        return result;
    }
};

/**
 * angle normalize
 *
 * @tparam angle is double
 * @param angle - angle to normalize
 *
 * @return double - normalized angle
 */
double angleNormalize(double angle) {
    return (fmod((angle + PI), (2 * PI)) - PI);
}
    
