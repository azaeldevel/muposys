#include "Login.hh"

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
		conn.connect(sysappdb::datconex);
	}
	catch(octetos::db::SQLException& e)
	{		
		return;
	}
	sysappdb::Users user(1);
	if(user.checkpass(conn))
	{
		//std::cout << "Usuario DB : " << user.getName() << "\n";
		//std::cout << "Usuario GTK : " << txUser->get_text() << "\n";
		
		if((txUser->get_text() == Glib::ustring(user.getName()))  and (txPassword->get_text() == Glib::ustring(user.getPwdtxt())))
		{
			lbMessage->set_text("OK clicked");
		}
		else
		{
			lbMessage->set_text("Usuario/Contraseña no coinciden");
		}
	}
	else
	{
		lbMessage->set_text("Fallo la descarga de base de datos");
	}
	
	conn.close();
    close();
}

void Login::on_cancel_button_clicked()
{
    lbMessage->set_text("Cancel clicked");
}