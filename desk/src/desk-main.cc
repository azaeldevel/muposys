
#include <gtkmm.h>
#include <iostream>

#if __linux__
	#include "config.h"
#elif MSYS2
    #include "config-cb.h"
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
