
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


#include <gtkmm.h>
#include <iostream>

#ifdef __linux__

#elif defined MSYS2

#else
	#error "Plataforma desconocida."
#endif

#include "desk.hh"


int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);

	mps::v0::Main* _main_ = NULL;
	try
	{
#ifdef OCTETOS_MUPOSYS_DESK_TDD_V0
		_main_ = new mps::v0::Main(true);
#else
		_main_ = new mps::v0::Main;
#endif
		if (_main_) kit.run(*_main_);
	}
	catch (const std::exception& e)
	{
		Gtk::MessageDialog dlg("Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();
		return EXIT_FAILURE;
	}
	//if(_main_) delete _main_;

	return EXIT_SUCCESS;
}
