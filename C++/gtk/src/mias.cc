
#include <gtkmm.h>
#include <iostream>

#include "config.h"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include "mias.hh"

namespace mps::mias
{

Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& glade) : mps::Muposys(cobject,glade), builder(glade)
{
	set_title(_("Mias Pizza & Pasta"));
	
}

Mias::~Mias()
{
}



}









int main (int argc, char *argv[])
{
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
	
	Gtk::Main kit(argc, argv);


	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create_from_resource("/mps/muposys.ui");
	}
	catch (const Glib::FileError & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	mps::Muposys* wnd_Main = 0;
	builder->get_widget_derived("wnd_Main", wnd_Main);


	if (wnd_Main)
	{
		kit.run(*wnd_Main);
	}
	return 0;
}