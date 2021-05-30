/* main_window.cc
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

#include "main_window.hh"

MainWindow::MainWindow()
	: Glib::ObjectBase("MainWindow")
	, Gtk::Window()
	, headerbar(nullptr)
	, root(nullptr) {

	headerbar = new Gtk::HeaderBar();
	headerbar->set_show_close_button();
	headerbar->set_title("RIP_RLB");
	set_titlebar(*headerbar);
	headerbar->show();

	for(int i = 0; i < 4; i++) {
		stateTitles[i] = new Gtk::Label(titles[i]);
		stateValues[i] = new Gtk::Label("0");
	}

	stateGrid = new Gtk::Grid();
	stateGrid->set_row_homogeneous(true);
	stateGrid->set_column_homogeneous(true);

	for (int i = 0; i < 4; i++) {
		stateGrid->attach(*(stateTitles[i]), 0, i, 1, 1);
		stateGrid->attach(*(stateValues[i]), 1, i, 1, 1);
	}

	stateLabel = new Gtk::Label("Current state");

	controls = new Gtk::ButtonBox();
	run = new Gtk::Button("Run");
	stop = new Gtk::Button("Stop");
	controls->pack_start(*run);
	controls->pack_start(*stop);

	root = new Gtk::VBox();
	root->pack_start(*stateLabel);
	root->pack_start(*stateGrid);
	root->pack_start(*controls);

	add(*root);
	show_all_children();
}

Gtk::Button* MainWindow::getRunButton() {
	return run;
}


Gtk::Button* MainWindow::getStopButton() {
	return stop;
}

Gtk::Label** MainWindow::getStateLabels() {
	return stateValues;
}
