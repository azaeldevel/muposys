
#include <gtkmm.h>
#include <iostream>

#include "config.h"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include "desk.hh"


int main (int argc, char *argv[])
{
	/*
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
	*/
	
	Gtk::Main kit(argc, argv);

	//Load the Glade file and instiate its widgets:
	/*Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create();
		std::string fileui;
#ifdef MUPOSYS_DESK_ENABLE_TDD
		fileui = PACKAGE_SRC_DIR;
#else
		fileui = PACKAGE_DATA_DIR;
#endif
		fileui += "/muposys.ui";
		builder->add_from_file(fileui);
	}
	catch (const Glib::FileError& e)
	{
		Gtk::MessageDialog dlg("Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();
		return EXIT_FAILURE;
	}
	catch (const std::exception& e)
	{
		Gtk::MessageDialog dlg("Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();
		return EXIT_FAILURE;		
	}*/
	
	mps::Main* Main;
	try
	{
#ifdef MUPOSYS_DESK_ENABLE_TDD
		//builder->get_widget_derived("Main", Main,true);
		Main = new mps::Main(true);
#else
		//builder->get_widget_derived("Main", Main);
		Main = new mps::Main;
#endif	
		if (Main) kit.run(*Main);
	}
	catch (const std::exception& e)
	{
		Gtk::MessageDialog dlg("Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();
		return EXIT_FAILURE;		
	}
	
	return EXIT_SUCCESS;
}
