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
    static const unsigned short SIZE = 4;

    //All these values are in radians.
    //0 - pendulum angle
    //1 - pendulum angular velocity
    //2 - motor angle
    //3 - motor angular velocity
    double mStateParam[SIZE];

public:
    State (double pendulumAngle = 0.0, double pendulumAngularVelocity = 0.0,
           double motorAngle = 0.0, double motorAngularVelocity = 0.0)
            : mStateParam{angleNormalize(pendulumAngle),
                          angleNormalize(motorAngle), pendulumAngularVelocity,
                          motorAngularVelocity} {}
    State (const State& state) {
        (*this) = state;
    }

    //Getters
    double getPendulumAngle () {
        return mStateParam[0];
    }
    double getPendulumAngle () const {
        return mStateParam[0];
    }
    double getMotorAngle () {
        return mStateParam[2];
    }
    double getMotorAngle () const {
        return mStateParam[2];
    }
    double getPendulumAngularVelocity () {
        return mStateParam[1];
    }
    double getPendulumAngularVelocity () const {
        return mStateParam[1];
    }
    double getMotorAngularVelocity () {
        return mStateParam[3];
    }
    double getMotorAngularVelocity () const {
        return mStateParam[3];
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
    void setPendulumAngle (const double pendulumAngle) {
        mStateParam[0] = angleNormalize(pendulumAngle);
    }
    void setMotorAngle (const double motorAngle) {
        mStateParam[2] = angleNormalize(motorAngle);
    }
    void setPendulumAngularVelocity (const double pendulumAngularVelocity) {
        mStateParam[1] = pendulumAngularVelocity;
    }
    void setMotorAngularVelocity (const double motorAngularVelocity) {
        mStateParam[3] = motorAngularVelocity;
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
    double& operator[] (const unsigned int index) {
        if (index >= SIZE) {
            throw "Index out of range";
        }

        return *(mStateParam + index);
    }
    const double& operator[] (const unsigned int index) const {
        if (index >= SIZE) {
            throw "Index out of range";
        }

        return *(mStateParam + index);
    }

    /**
     * compare two states
     *
     * @tparam state is of the {State &} type
     * @param state - the second state to compare with it
     *
     * @return bool - true if the two states are the same
     */
    bool operator== (const State& state) {
        bool result = true;

        for (int i = 0; i < SIZE && result; i++) {
            result = result && ((*this)[i] == state[i]);
        }

        return result;
    }
    bool operator== (const State& state) const {
        return (*this) == state;
    }

    State& operator= (const State& state) {

        if (this == &state) {
            return *this;
        }


        for (int i = 0; i < (*this).size(); i++) {
            (*this)[i] = state[i];
        }
        return *this;
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
double angleNormalize(const double angle) {
    return (fmod((angle + PI), (2 * PI)) - PI);
}
    
