
#include "muposys.hh"

namespace mps
{

Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	set_title(_("Multi-Porpuse System"));
	
}
Main::~Main()
{
	
}




Pizza::Pizza(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& glade) : Main(cobject,glade)
{
	
}

Pizza::~Pizza()
{
}




}

