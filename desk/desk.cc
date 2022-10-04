
#include <gtkmm/application.h>

#include "desk.hh"
#include "../apidb/muposysdb.hpp"

namespace mps
{

Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{	
	hb_muposys = 0;
	builder->get_widget("hb_muposys", hb_muposys);	
	//hb_muposys->set_subtitle(_("Multi-Porpuse Software System"));
	
	lbUser = 0;
	builder->get_widget("lbUser", lbUser);
		
	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
	show();
}

Main::~Main()
{
}

void Main::check_session()
{
	builder->get_widget_derived("Login", login);
	login->set_transient_for((Gtk::Window&)*this);
	int res = Gtk::RESPONSE_NONE;
	do
	{
		if (login)
		{
			res = login->run();
		}	
		switch(res)
		{
		case Gtk::RESPONSE_OK:
			break;	
		case Gtk::RESPONSE_CANCEL:
			login->close();
			return;	
		case Gtk::RESPONSE_NONE:
			break;			
		}
	}
	while(not login->get_credential().valid);
	
	
	if(login->get_credential().valid)
	{	
		//std::cout << "User valid " << login->get_credential().user << "..\n";
		credential = login->get_credential();
		lbUser->set_text(credential.user);
	}
	login->close();
}


Login::Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Dialog(cobject), builder(refGlade), retcode(Gtk::RESPONSE_NONE)
{
	lbmsg = 0;
	builder->get_widget("msg", lbmsg);
	
	btOK = 0;
	builder->get_widget("btOK", btOK);
	btOK->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_ok_clicked));
	
	btCancel = 0;
	builder->get_widget("btCancel", btCancel);
	btCancel->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_cancel_clicked));
		
	inPwd = 0;
	builder->get_widget("inPwd", inPwd);
	
	inUser = 0;
	builder->get_widget("inUser", inUser);
	//inUser->signal_key_press_event().connect(sigc::mem_fun(*this,&Login::on_in_user_enter));
	
	set_default_size(250,150);
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
	check_user();
	close();	
}

bool Login::on_in_user_enter(GdkEventKey* e)
{
	//if(e->keyval == GDK_KEY_KP_Enter)
	{
		std::cout << "Enter detected\n";
		inPwd->set_text("");
		inPwd->grab_focus();
	}
	
	return false;
}

void Login::check_user()
{
	Connector connDB;
	bool flag = false;
	int res = 0;
	try
	{
		flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		Gtk::MessageDialog dlg(*this,"Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		res = dlg.run();
		return;		
	}
	
	credential.valid = true;
	
	std::string strwhere = "name = ";
	strwhere += "'" + inUser->get_text() + "' and pwdtxt = '" + inPwd->get_text() + "' and status = 'A'";
	std::vector<muposysdb::Users*>* userlst = muposysdb::Users::select(connDB,strwhere);
	
	//std::cout << "SQL str : " << strwhere << "\n";
	
	if(userlst == NULL) 
	{
		credential.valid = false;
		//std::cout << "No hay resultado de la consulta\n";
	}
	if(userlst->size() == 0) 
	{		
		credential.valid = false;
		//std::cout << "Hay 0 resultados de la consulta\n";
	}
	if(userlst->size() > 1) 
	{
		credential.valid = false;
		//std::cout << "Hay " <<  userlst->size() << " resultados de la consulta\n";
	}	
	
	if(not credential.valid)//si no es valido el usario liberar memorio y salir
	{
		lbmsg->set_text("Usuario/Contraseña incorrectos.");
		for(auto u : *userlst)
		{
			if(u->getPerson().downName1(connDB))
			{
				if(u->getPerson().downName3(connDB))
				{
					credential.name = u->getPerson().getName1() + " " + u->getPerson().getName3();
				}
			}
			else
			{
				credential.name = u->getPerson().getName1();
			}
			delete u;
		}
		delete userlst;		
		return;
	}
	//std::cout << "Usuario aceptado\n";
	credential.user = inUser->get_text();
}
const Login::Credential& Login::get_credential() const
{
	return credential;
}
}

