

#ifndef MUPOSYS_MIAS_MAIN_HH
#define MUPOSYS_MIAS_MAIN_HH

#include "muposys.hh"


namespace mps::mias
{

class Mias : public mps::Muposys
{
public:
	/**
	*
	**/
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Mias();
	
private:
	const Glib::RefPtr<Gtk::Builder>& builder;
};

}

#endif