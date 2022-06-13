

#ifndef MUPOSYS_MIAS_MAIN_HH
#define MUPOSYS_MIAS_MAIN_HH

#include <gtkmm.h>//#include "muposys.hh"

namespace mps//::mias
{

class Main /*: public mps::Pizza*/
{
public:
	Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Main();

private:

};

}

#endif
