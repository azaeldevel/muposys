
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

#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
    #include <iostream>
#endif // OCTETOS_MUPOSYS_DESK_V1_TDD

#include "desk.hh"

namespace oct::mps::v1
{


Main::Main() : devel(false)
{
	init();

	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
	show();
#endif
}
Main::Main(bool d) : devel(d)
{
	init();

	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
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

#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
	/*int page_index = nbMain.append_page(sales);
	sales.set_info(nbMain,page_index);*/
	set_default_size(800,640);
	show_all_children();
#endif

    //login.signal_logged().connect(sigc::mem_fun(*this,&Main::on_logged));
    on_logged_listener(sigc::mem_fun(*this,&Main::on_logged));
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


const User& Main::get_user()const
{
    return login.get_user();
}
void Main::on_logged()
{
#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
    //std::cout << "Logged\n";
#endif

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
	actual_user.valid = false;
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
	cave0::mmsql::Data dtm = default_dtm0();
	bool conectfl = false;
	cave0::mmsql::Connection conn;
	try
	{
		conectfl = conn.connect(dtm, true);
	}
	catch (const cave0::ExceptionDriver& e)
	{
		return;
	}
	catch (const std::exception& e)
	{
		return;
	}
	catch (...)
	{
	}
	if(conectfl)
    {

    }

    std::vector<User> lstUser;
    std::string strsql = " name ='" + inUser.get_text() + "' and pwdtxt = '" + inPwd.get_text() + "'";
    bool lstUserflag = false;
    try
    {
 		 lstUserflag = conn.select(lstUser,strsql);
	}
	catch (const cave0::ExceptionDriver&)
	{
	}
	catch (...)
	{
	}

	if(lstUserflag)
	{
	    //std::cout << "Register : " + std::to_string(lstUser.size()) + "\n";
	    if(lstUser.size() == 1)
        {
            actual_user = lstUser[0];
        }
        else
        {

        }
	}

}
void Login::set_session(const char* u,const char* p)
{
	inUser.set_text(u);
	inPwd.set_text(p);
}
void Login::on_response(int res)
{

    if(not actual_user.valid)
    {
        lbMessage.set_text("Usuario/Contrasena invalido...");
    }

	if(actual_user.valid and res == Gtk::RESPONSE_OK)
	{
		_signal_logged.emit();
		hide();
	}
	else if(actual_user.valid and res == Gtk::RESPONSE_CANCEL)
	{
		hide();
	}
}
const User& Login::get_user()const
{
    return actual_user;
}
Login::signal_logged_t Login::signal_logged()
{
    return _signal_logged;
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

