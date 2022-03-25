
#include "muposys.hh"

namespace mps
{

Muposys::Muposys(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	set_title(_("Multi-Porpuse System"));
	
}
Muposys::~Muposys()
{
	
}
}

