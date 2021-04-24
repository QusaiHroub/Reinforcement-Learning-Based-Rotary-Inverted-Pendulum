/* util/pstate.hh
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

#ifndef PSTATE_HH
#define PSTATE_HH

#include "type.hh"
#include "math.hh"

class PState {
	struct Box {
		virtual void setValue (const float_4b value) = 0;
		virtual float_4b getValue () const = 0;
		Box &operator= (const float_4b value) {
			setValue (value);
			return *this;
		}
	};

	class Angle: public Box {
		float_4b mValue;
	public:
		void setValue (const float_4b value) {
			mValue = angleNormalize (value);
		}

		float_4b getValue() const {
			return mValue;
		}
	};

	class Velocity: public Box {
		float_4b mValue;
	public:
		void setValue (const float_4b value) {
			mValue = value;
		}

		float_4b getValue() const {
			return mValue;
		}
	};

	static const size_16b SIZE = 4;

    //0 - pendulum angle - must be in radians
    //1 - pendulum angular velocity - must be in radians/second
    //2 - motor angle - must be in radians
    //3 - motor angular velocity - must be in radians/second
    Box *mStateParam[SIZE];

public:
    PState (float_4b pendulumAngle = 0.0, float_4b pendulumAngularVelocity = 0.0,
           float_4b motorAngle = 0.0, float_4b motorAngularVelocity = 0.0) {

           mStateParam[0] = dynamic_cast <Box *> (new Angle());
           *mStateParam[0] = pendulumAngle;
           mStateParam[2] = dynamic_cast <Box *> (new Angle());
           *mStateParam[2] = motorAngle;
           mStateParam[1] = dynamic_cast <Box *> (new Velocity());
           *mStateParam[1] = pendulumAngularVelocity;
           mStateParam[3] = dynamic_cast <Box *> (new Velocity());
           *mStateParam[3] = motorAngularVelocity;
	}

    PState (const PState& state) {
        (*this) = state;
    }

    //Getters
    float_4b getPendulumAngle () {
        return mStateParam[0]->getValue ();
    }
    float_4b getPendulumAngle () const {
        return mStateParam[0]->getValue ();
    }
    float_4b getMotorAngle () {
        return mStateParam[2]->getValue ();
    }
    float_4b getMotorAngle () const {
        return mStateParam[2]->getValue ();
    }
    float_4b getPendulumAngularVelocity () {
        return mStateParam[1]->getValue ();
    }
    float_4b getPendulumAngularVelocity () const {
        return mStateParam[1]->getValue ();
    }
    float_4b getMotorAngularVelocity () {
        return mStateParam[3]->getValue ();
    }
    float_4b getMotorAngularVelocity () const {
        return mStateParam[3]->getValue ();
    }

    /**
     * size
     *
     * @return const unsigned short - represent the number of data members
     */
    size_16b size() const {
        return SIZE;
    }

    //Setters
    void setPendulumAngle (const float_4b pendulumAngle) {
        mStateParam[0]->setValue (pendulumAngle);
    }
    void setMotorAngle (const float_4b motorAngle) {
        mStateParam[2]->setValue (motorAngle);
    }
    void setPendulumAngularVelocity (const float_4b pendulumAngularVelocity) {
        mStateParam[1]->setValue (pendulumAngularVelocity);
    }
    void setMotorAngularVelocity (const float_4b motorAngularVelocity) {
        mStateParam[3]->setValue (motorAngularVelocity);
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
     * @return &PState::Box - the value of data member at that index
     */
    Box& operator[] (const unsigned short index) {
        if (index >= SIZE) {
            throw "Index out of range";
        }

        return **(mStateParam + index);
    }
    const Box& operator[] (const unsigned short index) const {
        if (index >= SIZE) {
            throw "Index out of range";
        }

        return **(mStateParam + index);
    }

    /**
     * compare two states
     *
     * @tparam state is of the {State &} type
     * @param state - the second state to compare with it
     *
     * @return bool - true if the two states are the same
     */
    bool operator== (const PState &state) {
        bool result = true;

        for (int i = 0; i < SIZE && result; i++) {
            result = result && (mStateParam[i]->getValue () == state[i].getValue ());
        }

        return result;
    }
    bool operator== (const PState &state) const {
        return (*this) == state;
    }

    PState& operator= (const PState &state) {

        if (this == &state) {
            return *this;
        }

        for (int i = 0; i < (*this).size(); i++) {
            *mStateParam[i] = state[i];
        }
        return *this;
    }

    /**
     * set At - interface to setters
     *
     * @tparam index is of the {const unsigned short} type
     * @tparam float_4b is of the {float_4b} type
     * @param index - the index of the value you want to set/reblace
     * @param value - the new value to be set
     *
     */
    void setAt(const size_16b index, float_4b value) {
        *mStateParam[index] = value;
    }
};

#endif