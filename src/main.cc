/* main.hh
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

#include <memory>

#include "main_window.hh"

static void on_activate (Glib::RefPtr<Gtk::Application> app) {
    static std::unique_ptr<Gtk::Window> window;

    if (!window) {
		window = std::make_unique<MainWindow>();
		window->property_application() = app;
		window->property_default_width() = 600;
		window->property_default_height() = 300;
		app->add_window(*window);
	}

	window->present();
}


int main (int argc, char *argv[]) {
    int ret;

	Glib::RefPtr<Gtk::Application> app =
		Gtk::Application::create("org.example.App", Gio::APPLICATION_FLAGS_NONE);

	app->signal_activate().connect(sigc::bind(&on_activate, app));

	ret = app->run(argc, argv);

	return ret;
}
