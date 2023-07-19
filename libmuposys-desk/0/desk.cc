
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


Main::Main() : devel(false)
{
	init();

#ifdef OCTETOS_MUPOSYS_DESK_TDD_V0
	show();
#endif
}
Main::Main(bool d) : devel(d)
{
	init();

#ifdef OCTETOS_MUPOSYS_DESK_TDD_V0
	show();
#endif
}
void Main::init()
{
	//add_events(Gdk::KEY_PRESS_MASK);
	signal_show().connect(sigc::mem_fun(*this,&Main::on_login));

	set_titlebar(header);
	set_title("Multi-Porpuse Software System");
	set_subtitle("muposys");
	header.set_show_close_button(true);

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

#ifdef OCTETOS_MUPOSYS_DESK_TDD_V0
	//int page_index = nbMain.append_page(sales);
	//sales.set_info(nbMain,page_index);
	set_default_size(800,640);
	show_all_children();
#endif
}
Main::~Main()
{
}
void Main::on_login()
{
	login.set_transient_for(*this);
	login.set_modal();
	login.show();

	//if(devel) login.set_session("root","123456");
	int res = Gtk::RESPONSE_NONE;
	/*do
	{
		res = login.run();
		switch(res)
		{
		case Gtk::RESPONSE_OK:
			break;
		case Gtk::RESPONSE_CANCEL:
			login.close();
			return;
		case Gtk::RESPONSE_NONE:
			break;
		}
	}
	while(not login.get_credential().valid);*/

	/*if(login.get_credential().valid)
	{
		credential = login.get_credential();
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
		if(credential.userdb.downName(connDB))
		if(credential.userdb.downPerson(connDB))
		{
			if(credential.userdb.getPerson().downName1(connDB)) credential.name = credential.userdb.getPerson().getName1();
			if(credential.userdb.getPerson().downName3(connDB)) credential.name += " " + credential.userdb.getPerson().getName3();
			lbUser.set_text(credential.name);
		}
		connDB.close();
	}
	login.close();*/
	//this->notific_session();
}
/*void Main::add_activity(Gtk::Widget& w)
{
	nbMain.append_page(w);
}*/
/*void Main::set_title(const char* t )
{
	header.set_title(t);
}*/
void Main::set_subtitle(const char* t )
{
	header.set_subtitle(t);
}
#ifdef OCTETOS_MUPOSYS_DESK_TDD_V0

#endif
/*const muposysdb::User& Main::get_user() const
{
	return credential.userdb;
}*/
void Main::notific_session()
{
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

