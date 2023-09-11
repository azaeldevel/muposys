
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
	//#include "config.h"
#elif defined MSYS2
    //#include "config-cb.h"
#else
	#error "Plataforma desconocida."
#endif

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include "desk.hh"


int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);

	mps::Main* _main_ = NULL;
	try
	{
#ifdef MUPOSYS_DESK_ENABLE_TDD
		_main_ = new mps::Main(true);
#else
		_main_ = new mps::Main;
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
