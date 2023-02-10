
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

#include <iostream>

#include "desk-v1.hh"
#include "ds-v1.hh"

#ifdef __linux__
	#include "config.h"
#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida."
#endif


namespace mps::v1
{


//Login::Credential Main::credential;
Main::Main() : devel(false),box_header(Gtk::Orientation::HORIZONTAL),box_header_info(Gtk::Orientation::HORIZONTAL),box_header_controls(Gtk::Orientation::HORIZONTAL),boxSlices(Gtk::Orientation::VERTICAL)
{
	init();

	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
#ifdef MUPOSYS_DESK_ENABLE_TDD
	show();
#endif
}
Main::Main(bool d) : devel(d),box_header(Gtk::Orientation::HORIZONTAL),box_header_info(Gtk::Orientation::HORIZONTAL),box_header_controls(Gtk::Orientation::HORIZONTAL),boxSlices(Gtk::Orientation::VERTICAL)
{
	init();

	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
#ifdef MUPOSYS_DESK_ENABLE_TDD
	show();
#endif
}
void Main::init()
{
	//add_events(Gdk::KEY_PRESS_MASK);
    title = "Multi-Porpuse Software System";
	set_title(title);
	//header.set_title_widget(title);
	header.set_show_title_buttons(true);
	set_titlebar(header);
	//set_subtitle("muposys");
	//set_titlebar(title);
	//title.show();

	header.pack_start(box_header);
	box_header.prepend(box_header_controls);
	box_header.prepend(sep_header);//,false,true,10
	box_header.prepend(box_header_info);

	box_header_info.prepend(lbUser);

	box_header_controls.prepend(btHome);
	box_header_controls.prepend(btSysMang);
	box_header_controls.prepend(btLogout);
	box_header_controls.prepend(btAbout);

	btHome.set_image_from_icon_name("go-home");
	btSysMang.set_image_from_icon_name("preferences-system");
	btLogout.set_image_from_icon_name("system-log-out");
	btAbout.set_image_from_icon_name("help-about");

	btHome.set_tooltip_text("Aplicacion principal");
	btSysMang.set_tooltip_text("Administración de MUPOSYS");
	btLogout.set_tooltip_text("Cerrar seción de usuario actual");
	btAbout.set_tooltip_text("Acerca de MUPOSYS");

	//add(boxSlices);
	//boxSlices.prepend(tbMain);//,false,true
	boxSlices.prepend(nbMain);//,false,true
	login.set_title(title);

#ifdef MUPOSYS_DESK_ENABLE_TDD
	//int page_index = nbMain.append_page(sales);
	//sales.set_info(nbMain,page_index);
	set_default_size(800,640);
	//show_all_children();
#endif
}
Main::~Main()
{
}
void Main::check_session()
{
	login.set_transient_for(*this);
	login.set_modal(true);
	//login.show_all_children();
	if(devel) login.set_session("root","123456");

    int response = login.run();

	//login.close();
	//this->notific_session();
}
void Main::add_activity(Gtk::Widget& w)
{
	nbMain.append_page(w);
}
/*void Main::set_title(const char* t )
{
	header.set_title(t);
}
void Main::set_subtitle(const char* t )
{
	header.set_subtitle(t);
}*/
#ifdef MUPOSYS_DESK_ENABLE_TDD

#endif
const User& Main::get_user() const
{

}
const Glib::ustring& Main::get_title()const
{
    return title;
}
void Main::notific_session()
{
}

Main::Title::Title() : Box(Gtk::Orientation::VERTICAL),title("Multi-porpuse Sofware System"),subtitle("MUPOSYS")
{
    init();
}
Main::Title::Title(const Glib::ustring& t) : Box(Gtk::Orientation::VERTICAL),title(t),subtitle("MUPOSYS")
{
    init();
}
Main::Title::Title(const Glib::ustring& t, const Glib::ustring st) : Box(Gtk::Orientation::VERTICAL),title(t),subtitle(st)
{
    init();
}
void Main::Title::init()
{
    append(title);
    append(subtitle);

	Cairo::FontOptions font = subtitle.get_font_options();

}













Login::Login() : childs(Gtk::Orientation::VERTICAL)
{
	init();
}
Login::Login(const Glib::ustring& t, Gtk::Window& p, bool m) : Gtk::Dialog(t,p,m)
{
	init();
}
void Login::init()
{
    set_child(childs);
	childs.append(boxUser);//,false,true
	childs.append(boxPass);
	childs.append(lbMessage);
	childs.append(boxButtons);

	lbUser.set_text("Usuario         : ");
	boxUser.append(lbUser);
	boxUser.append(inUser);

	lbPass.set_text("Constraseña : ");
	boxPass.append(lbPass);
	boxPass.append(inPwd);
	inPwd.set_visibility(false);

	boxButtons.set_spacing(10);
	boxButtons.append(btOK);
	boxButtons.append(btCancel);

	btCancel.signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_cancel_clicked));
	btOK.signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_ok_clicked));
	signal_response().connect(sigc::mem_fun(*this, &Login::on_response) );

	//btOK.set_image_from_icon_name("gtk-ok");
	btOK.set_label("O.K.");
	//btCancel.set_image_from_icon_name("gtk-cancel");
    btCancel.set_label("Cancel");

	set_default_size(250,100);
}
Login::~Login()
{
}
void Login::on_bt_cancel_clicked()
{
    //std::cout << "\tCANCEL\n";
	response(CANCEL);
}
void Login::on_bt_ok_clicked()
{
    //std::cout << "\tOK\n";
	response(OK);
}
bool Login::check_user()
{
    //std::cout << "Checking 1..\n";
	cave_current::OCTETOS_CAVE_DRIVER::Connection connDB;
	bool flag = false;
	int res = 0;
	try
	{
		flag = connDB.connect(ds,true);
	}
	catch(const std::exception& e)
	{
	    Gtk::MessageDialog dlg("Error detectado.",false,Gtk::MessageType::ERROR,Gtk::ButtonsType::OK_CANCEL,true);
        dlg.set_secondary_text(e.what());
        dlg.show();
		return false;
	}
    //std::cout << "Checking 2..\n";

	credential.valid = true;

    //std::cout << "Checking 3..\n";

	std::string strwhere = "name = ";
	strwhere += "'" + inUser.get_text() + "' and pwdtxt = '" + inPwd.get_text() + "' and status = 3";
	std::vector<User> userlst;
	try
	{
		auto resutl = connDB.select("person,name","User",strwhere);
        resutl.store(userlst);
	}
	catch(const std::exception& e)
	{
	    //std::cout << "Error detedtado..\n";
	    Gtk::MessageDialog dlg("Error detectado.",false,Gtk::MessageType::ERROR,Gtk::ButtonsType::OK_CANCEL,true);
        dlg.set_secondary_text(e.what());
        dlg.show();
		return false;
	}

	//std::cout << "SQL str : " << strwhere << "\n";

	if(userlst.size() == 0)
	{
		credential.valid = false;
		//std::cout << "Hay 0 resultados de la consulta\n";
		return false;
	}
	if(userlst.size() > 1)
	{
		credential.valid = false;
		//std::cout << "Hay " <<  userlst.size() << " resultados de la consulta\n";
		return false;
	}

    //std::cout << "Checking 4..\n";

	strwhere = "id = " + std::to_string(userlst.front().person);
	//std::cout << "SQL str : " << strwhere << "\n";
	std::vector<Person> personslst;
	try
	{
		auto resutlPerson = connDB.select("name1,name3","Person",strwhere);
        resutlPerson.store(personslst);
	}
	catch(const std::exception& e)
	{
	    //std::cout << "Error detedtado..\n";
	    Gtk::MessageDialog dlg("Error detectado.",false,Gtk::MessageType::ERROR,Gtk::ButtonsType::OK_CANCEL,true);
        dlg.set_secondary_text(e.what());
        dlg.show();
		return false;
	}
    if(personslst.size() == 0)
	{
		credential.valid = false;
		//std::cout << "Hay 0 resultados de la consulta\n";
		return false;
	}
	if(personslst.size() > 1)
	{
		credential.valid = false;
		//std::cout << "Hay " <<  personslst.size() << " resultados de la consulta\n";
		return false;
	}

	//std::cout << "Usuario aceptado\n";
	credential.name = personslst.front().name1;
	if(not personslst.front().name3.empty()) credential.name += " " + personslst.front().name3;
	credential.user = inUser.get_text();
	credential.userdb = userlst.front();
    //std::cout << "Checking 5..\n";
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
    //std::cout << "Response detected\n";
    if(res == OK)
    {
        if(check_user()) close();
        else
        {
            lbMessage.set_text("Usuario/Contrasenas incorrectos...");
        }
    }
    else if(res == CANCEL)
    {
        close();
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

