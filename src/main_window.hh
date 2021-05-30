/* main_window.hh
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

#include <gtkmm.h>
#include <string>

class MainWindow : public Gtk::Window {
public:
	MainWindow();

	Gtk::Button* getRunButton();
	Gtk::Button* getStopButton();
	Gtk::Label** getStateLabels();

private:
	std::string titles[4] = {"Pendulum angle",
							 "Pendulum angular velocity",
							 "Motor angle",
							 "Motor angular velocity"};
	Gtk::HeaderBar *headerbar;
	Gtk::Grid *stateGrid;
	Gtk::Label *stateTitles[4];
	Gtk::Label *stateValues[4];
	Gtk::VBox *root;
	Gtk::Label *stateLabel;
	Gtk::ButtonBox *controls;
	Gtk::Button *run;
	Gtk::Button *stop;
};