
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
	//#include "config.h"
#elif MSYS2
    //#include "config-cb.h"
#else
	#error "Plataforma desconocida."
#endif


namespace mps
{

Login::Credential Main::credential;
Main::Main() : devel(false)
{
	init();

	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
#ifdef MUPOSYS_DESK_V0_ENABLE_TDD
	show();
#endif
}
Main::Main(bool d) : devel(d)
{
	init();

	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
#ifdef MUPOSYS_DESK_V0_ENABLE_TDD
	show();
#endif
}
void Main::init()
{
	add_events(Gdk::KEY_PRESS_MASK);

	set_title("Multi-Porpuse Software System");
	set_subtitle("muposys");
	header.set_show_close_button(true);
	set_titlebar(header);

	header.pack_start(box_header);
	box_header.pack_start(box_header_controls);
	box_header.pack_start(sep_header,false,true,10);
	box_header.pack_start(box_header_info);

	box_header_info.pack_start(lbUser);

	box_header_controls.pack_start(btHome);
	box_header_controls.pack_start(btSysMang);
	box_header_controls.pack_start(btLogout);
	box_header_controls.pack_start(btAbout);

	btHome.set_image_from_icon_name("go-home");
	btSysMang.set_image_from_icon_name("preferences-system");
	btLogout.set_image_from_icon_name("system-log-out");
	btAbout.set_image_from_icon_name("help-about");

	btHome.set_tooltip_text("Aplicacion principal");
	btSysMang.set_tooltip_text("Administración de MUPOSYS");
	btLogout.set_tooltip_text("Cerrar seción de usuario actual");
	btAbout.set_tooltip_text("Acerca de MUPOSYS");

	add(boxSlices);
	boxSlices.pack_start(tbMain,false,true);
	boxSlices.pack_start(nbMain,false,true);

#ifdef MUPOSYS_DESK_V0_ENABLE_TDD
	/*int page_index = nbMain.append_page(sales);
	sales.set_info(nbMain,page_index);*/
	set_default_size(800,640);
	show_all_children();
#endif
}
Main::~Main()
{
}
void Main::check_session()
{
	login.set_transient_for(*this);
	login.set_modal(true);
	if(devel) login.set_session("root","123456");
	login.show();
}
void Main::add_activity(Gtk::Widget& w)
{
	nbMain.append_page(w);
}
void Main::set_title(const char* t )
{
	header.set_title(t);
}
void Main::set_subtitle(const char* t )
{
	header.set_subtitle(t);
}
#ifdef MUPOSYS_DESK_V0_ENABLE_TDD

#endif
/*const muposysdb::User& Main::get_user() const
{
	return credential.userdb;
}*/
void Main::notific_session()
{
}
















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

	boxButtons.pack_start(btCancel);
	boxButtons.pack_start(btOK);

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
const Login::Credential& Login::get_credential() const
{
	return credential;
}
void Login::set_session(const char* u,const char* p)
{
	inUser.set_text(u);
	inPwd.set_text(p);
}
void Login::on_response(int res)
{
	if(credential.valid and res == Gtk::RESPONSE_OK)
	{
		hide();
	}
	else if(credential.valid and res == Gtk::RESPONSE_CANCEL)
	{
		hide();
	}
}
































Restaurant::Restaurant()
{
}
Restaurant::Restaurant(bool d) : Main(d)
{
}
Restaurant::~Restaurant()
{
}












}

