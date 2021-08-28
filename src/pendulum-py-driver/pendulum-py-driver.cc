/* pendulum_py_driver/pendulum_py_driver.cc
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

#include "../pendulum.hh"
#include "../utils/pstate.hh"
#include "../utils/type.hh"

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(pendulum_py_driver)
{
    using namespace boost::python;

    auto unBoxAt = static_cast<float_32b (PState::*)(size_16b)>(&PState::unBoxAt);
    auto getPendulumAngle = static_cast<float_32b (PState::*)()>(&PState::getPendulumAngle);
    auto getMotorAngle = static_cast<float_32b (PState::*)()>(&PState::getMotorAngle);
    auto getPendulumAngularVelocity = static_cast<float_32b (PState::*)()>(&PState::getPendulumAngularVelocity);
    auto getMotorAngularVelocity = static_cast<float_32b (PState::*)()>(&PState::getMotorAngularVelocity);

    class_<PState>("Pstate", init<float_32b, float_32b, float_32b, float_32b>())
        .def("size", &PState::size)
        .def("un_box_at", unBoxAt)
        .def("get_pendulum_angle", getPendulumAngle)
        .def("get_motor_angle", getMotorAngle)
        .def("get_penduluma_angular_velocity", getPendulumAngularVelocity)
        .def("get_motor_angular_velocity", getMotorAngularVelocity)
    ;

    class_<Pendulum>("Pendulum")
        .def("stop_motor", &Pendulum::stopMotor)
        .def("update_motor_pwm", &Pendulum::updateMotorPWM)
        .def("get_state", &Pendulum::getState)
    ;
}
