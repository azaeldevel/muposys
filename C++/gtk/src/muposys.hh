
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

namespace mps
{

class Muposys : public Gtk::Window
{
public:
/**
*
**/
	Muposys(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Muposys();

private:
	const Glib::RefPtr<Gtk::Builder>& builder;
};


}

#endif