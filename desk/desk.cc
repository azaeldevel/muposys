
#include "desk.hh"

namespace mps
{

Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	bt_close = 0;
	builder->get_widget("bt_close", bt_close);
	bt_close->signal_clicked().connect(sigc::mem_fun(*this,&Main::on_bt_close_clicked));
	
	hb_muposys = 0;
	builder->get_widget("hb_muposys", hb_muposys);	
	hb_muposys->set_subtitle(_("Multi-Porpuse Software System"));
		
	signal_show().connect(sigc::mem_fun(*this,&Main::check));
	show();
}

Main::~Main()
{
}

void Main::on_bt_close_clicked()
{
	close();
}

void Main::check()
{
	mps::Login* login = 0;
	builder->get_widget_derived("Login", login);
	
	int res = Gtk::RESPONSE_NONE;
	/*do
	{*/
		if (login)
		{
			res = login->run();
		}	
		/*switch(res)
		{
		case Gtk::RESPONSE_OK:
			break;	
		case Gtk::RESPONSE_CANCEL:
			return EXIT_FAILURE;	
		case Gtk::RESPONSE_NONE:
			break;			
		}
	}
	while(res != Gtk::RESPONSE_OK);*/
}


Login::Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Dialog(cobject), builder(refGlade), retcode(Gtk::RESPONSE_NONE)
{
	lbmsg = 0;
	builder->get_widget("msg", lbmsg);
	lbmsg->set_text("Tests...");
	
	btOK = 0;
	builder->get_widget("btOK", btOK);
	btOK->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_ok_clicked));
	
	btCancel = 0;
	builder->get_widget("btCancel", btCancel);
	btCancel->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_cancel_clicked));
	
	set_default_size(230,120);
	set_modal(true);
}

Login::~Login()
{
}

int Login::run()
{
	show();
	Gtk::Dialog::run();
	return retcode;
}

void Login::on_bt_cancel_clicked()
{
	retcode = Gtk::RESPONSE_CANCEL;
	close();
}

void Login::on_bt_ok_clicked()
{
	retcode = Gtk::RESPONSE_OK;
	close();	
}


}

