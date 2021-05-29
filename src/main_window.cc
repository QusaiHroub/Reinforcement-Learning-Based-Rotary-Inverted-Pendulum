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
	, headerbar(nullptr) {

	headerbar = new Gtk::HeaderBar();
	headerbar->set_show_close_button();
	headerbar->set_title("RIP_RLB");
	set_titlebar(*headerbar);
	headerbar->show();
}
