/* manager.hh
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

#ifndef MANAGER_HH
#define MANAGER_HH

#pragma once

#include "main_window.hh"
#include "pendulum.hh"

class Manager {
	std::unique_ptr<MainWindow> *mMainWindow;
	Pendulum pendulum;

public:
	Manager(std::unique_ptr<MainWindow> *);
};

Manager::Manager(std::unique_ptr<MainWindow> *mainWindow) : mMainWindow (mainWindow) {

}

#endif