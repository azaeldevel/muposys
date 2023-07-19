
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 *
 * muposys is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * muposys is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "desk.hh"

#if __linux__

#elif MSYS2

#else
	#error "Plataforma desconocida."
#endif


namespace mps::v0
{

Login::Login()
{
	init();
}
Login::Login(const Glib::ustring& t, Gtk::Window& p, bool m) : Gtk::Dialog(t,p,m)
{
	init();
}
void Login::init()
{
	get_vbox()->pack_start(boxUser,false,true);
	get_vbox()->pack_start(boxPass,false,true);
	get_vbox()->pack_start(lbMessage,false,true);
	get_vbox()->pack_start(boxButtons,false,true);

	lbUser.set_text("Usuario         : ");
	boxUser.pack_start(lbUser);
	boxUser.pack_start(inUser);

	lbPass.set_text("Constraseña : ");
	boxPass.pack_start(lbPass);
	boxPass.pack_start(inPwd);
	inPwd.set_visibility(false);

	boxButtons.pack_start(btOK);
	boxButtons.pack_start(btCancel);

	btCancel.signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_cancel_clicked));
	btOK.signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_ok_clicked));
	signal_response().connect(sigc::mem_fun(*this, &Login::on_response) );

	btOK.set_image_from_icon_name("gtk-ok");
	btCancel.set_image_from_icon_name("gtk-cancel");

	set_default_size(250,100);
	show_all_children();
}
Login::~Login()
{
}
void Login::on_bt_cancel_clicked()
{
	response(Gtk::RESPONSE_CANCEL);
}
void Login::on_bt_ok_clicked()
{
	check_user();
	response(Gtk::RESPONSE_OK);
}
void Login::check_user()
{
	/*Connector connDB;
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
	strwhere += "'" + inUser.get_text() + "' and pwdtxt = '" + inPwd.get_text() + "' and status = 3";
	std::vector<muposysdb::User*>* userlst = muposysdb::User::select(connDB,strwhere);

	//std::cout << "SQL str : " << strwhere << "\n";

	if(userlst == NULL)
	{
		credential.valid = false;
		std::cout << "No hay resultado de la consulta\n";
	}
	if(userlst->size() == 0)
	{
		credential.valid = false;
		std::cout << "Hay 0 resultados de la consulta\n";
	}
	if(userlst->size() > 1)
	{
		credential.valid = false;
		std::cout << "Hay " <<  userlst->size() << " resultados de la consulta\n";
	}

	if(not credential.valid)//si no es valido el usario liberar memorio y salir
	{
		lbMessage.set_text("Usuario/Contraseña incorrectos.");
		for(auto u : *userlst)
		{
			u->downPerson(connDB);
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
	credential.user = inUser.get_text();
	credential.userdb = *userlst->front();*/
}
/*const Login::Credential& Login::get_credential() const
{
	return credential;
}*/
void Login::set_session(const char* u,const char* p)
{
	inUser.set_text(u);
	inPwd.set_text(p);
}
void Login::on_response(int res)
{
	/*if(credential.valid and res == Gtk::RESPONSE_OK)
	{
		hide();
	}
	else
	{
		switch (res)
		{
		case Gtk::RESPONSE_CLOSE:
		case Gtk::RESPONSE_CANCEL:
		case Gtk::RESPONSE_DELETE_EVENT:
			hide();
			break;
		}
	}*/
}




}

