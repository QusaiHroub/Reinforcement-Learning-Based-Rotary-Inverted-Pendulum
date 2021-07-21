/* util/sstate.hh
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
#ifndef STATE
#define STATE

#include "math.hh"
#include "type.hh"

class State {
private:
    static const unsigned short SIZE = 4;

    //All these values are in radians.
    //0 - pendulum angle
    //1 - pendulum angular velocity
    //2 - motor angle
    //3 - motor angular velocity
    int_8b mStateParam[SIZE];

    void (State::*const setters[SIZE]) (const int_8b);

public:
    State (int_8b pendulumAngle = 0, int_8b pendulumAngularVelocity = 0,
           int_8b motorAngle = 0, int_8b motorAngularVelocity = 0)
            : mStateParam{pendulumAngle,
                          motorAngle, pendulumAngularVelocity,
                          motorAngularVelocity}, setters{&State::setPendulumAngle,
                          &State::setPendulumAngularVelocity, &State::setMotorAngle,
                          &State::setMotorAngularVelocity} {}

    State (const State& state): setters{&State::setPendulumAngle,
                          &State::setPendulumAngularVelocity, &State::setMotorAngle,
                          &State::setMotorAngularVelocity} {
        (*this) = state;
    }

    //Getters
    int_8b getPendulumAngle () {
        return mStateParam[0];
    }
    int_8b getPendulumAngle () const {
        return mStateParam[0];
    }
    int_8b getMotorAngle () {
        return mStateParam[2];
    }
    int_8b getMotorAngle () const {
        return mStateParam[2];
    }
    int_8b getPendulumAngularVelocity () {
        return mStateParam[1];
    }
    int_8b getPendulumAngularVelocity () const {
        return mStateParam[1];
    }
    int_8b getMotorAngularVelocity () {
        return mStateParam[3];
    }
    int_8b getMotorAngularVelocity () const {
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
    void setPendulumAngle (const int_8b pendulumAngle) {
        mStateParam[0] = pendulumAngle;
    }
    void setMotorAngle (const int_8b motorAngle) {
        mStateParam[2] = motorAngle;
    }
    void setPendulumAngularVelocity (const int_8b pendulumAngularVelocity) {
        mStateParam[1] = pendulumAngularVelocity;
    }
    void setMotorAngularVelocity (const int_8b motorAngularVelocity) {
        mStateParam[3] = motorAngularVelocity;
    }

    /**
     * intexing the data member of the state
     * You can't use this operator to assign. Use setAt instead of it.
     *
     * @tparam index is of the {const unsigned short} type
     * @param index - index of the data member
     *
     * @throws Index out of range when the index is more than or equal to
     * the size
     *
     * @return int_8b - the value of data member at that index
     */
    int_8b operator[] (const unsigned short index) {
        if (index >= SIZE) {
            throw "Index out of range";
        }

        return *(mStateParam + index);
    }
    const int_8b operator[] (const unsigned short index) const {
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
            result = result && (mStateParam[i] == state[i]);
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
            ((*this).*setters[i])(state[i]);
        }
        return *this;
    }

    /**
     * set At - interface to setters
     *
     * @tparam index is of the {const unsigned short} type
     * @tparam value is of the {int_8b} type
     * @param index - the index of the value you want to set/reblace
     * @param value - the new value to be set
     *
     */
    void setAt(const unsigned short index, int_8b value) {
        ((*this).*setters[index])(value);
    }
};

#endif
