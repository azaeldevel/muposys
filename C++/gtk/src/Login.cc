#include "Login.hh"
#include "muposysdb.hpp"

Login::Login()
{

}
Login::Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade):Gtk::Window(cobject), builder(refGlade)
{
	builder->get_widget("btAccept", btAccept);
    builder->get_widget("btCancel", btCancel);
    builder->get_widget("lbMessage", lbMessage);
    builder->get_widget("txUser", txUser);
    builder->get_widget("txPassword", txPassword);
    
    btAccept->signal_clicked().connect(sigc::mem_fun(*this, &Login::on_accept_button_clicked));
    btCancel->signal_clicked().connect(sigc::mem_fun(*this, &Login::on_cancel_button_clicked));
}

void Login::on_accept_button_clicked()
{
	octetos::db::mariadb::Connector conn;	
	try
	{
		conn.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{		
		std::cerr << e.what() << "\n";
		return;
	}
	muposysdb::Users* userbd = NULL;
	std::string strnamewhere= "name = '";
	strnamewhere += txUser->get_text() + "' and status = 'A'";
	std::vector<muposysdb::Users*>* usrlst = muposysdb::Users::select(conn,strnamewhere);
	if(usrlst->size() == 0)
	{
		lbMessage->set_text("Usuario/Contraseña no coinciden");
		return;
	}
	else if(usrlst->size() > 1) 
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de 
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		lbMessage->set_text("Erro en base de datos hay demasido coincidencias para este usuario");
		return;
	}
	else
	{
		userbd = usrlst->at(0);
	}
	
	if(userbd->checkpass(conn))
	{
		std::cout << "Usuario DB : " << userbd->getName() << "\n";
		std::cout << "Usuario Pw : " << userbd->getPwdtxt() << "\n";
		//std::cout << "Usuario GTK : " << txUser->get_text() << "\n";
		//std::cout << "Usuario GTK : " << txPassword->get_text() << "\n";
		if((txUser->get_text() == Glib::ustring(userbd->getName()))  and (txPassword->get_text() == Glib::ustring(userbd->getPwdtxt())))
		{
			lbMessage->set_text("OK clicked");
			//std::cout << "OK clicked\n";
		}
		else
		{
			lbMessage->set_text("Usuario/Contraseña no coinciden");
			//std::cout << "Usuario/Contraseña no coinciden\n";
		}
	}
	else
	{
		lbMessage->set_text("Fallo la descarga de base de datos");
		//std::cout << "Fallo la descarga de base de datos\n";
	}
	
	conn.close();
    close();
}

void Login::on_cancel_button_clicked()
{
    lbMessage->set_text("Cancel clicked");
}