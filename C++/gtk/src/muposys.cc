
#include "muposys.hh"

namespace mps
{

Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	
	bt_close = 0;
	builder->get_widget("bt_close", bt_close);
	bt_close->signal_clicked().connect(sigc::mem_fun(*this,&Main::on_bt_close_clicked));
	
	hb_muposys = 0;
	builder->get_widget("hb_muposys", hb_muposys);	
	hb_muposys->set_subtitle(_("Multi-Porpuse System"));
	
}
Main::~Main()
{
	
}

//
void Main::on_bt_close_clicked()
{
	close();
}


Pizza::Pizza(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& glade) : Main(cobject,glade)
{
	
}

Pizza::~Pizza()
{
}




}

