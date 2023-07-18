
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 *
 * muposys is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * muposys is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef __linux__

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida."
#endif

#include "desk-gtk-v1.hh"


int main (int argc, char *argv[])
{
	auto app = Gtk::Application::create("org.gtkmm.examples.base");

    return app->make_window_and_run<mps::v1::gtk::Main>(argc, argv);
}
