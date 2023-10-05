
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

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

#include <gtkmm.h>
#include <glibmm/i18n.h>
#include <gtkmm.h>

#ifdef __linux__

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida."
#endif

//#include "TableSaling.hh"
#include <muposys/core/1/core.hh>

namespace oct::mps::v1
{
    namespace cave = oct::cave::v0;

struct Person
{
    unsigned long id;

    std::string name1,name3; //person name

    Person() = default;
    Person(const char** s)
    {
        name1 = s[0];
    }
    Person(cave::Row<char,cave::mmsql::Data> s)
    {
        name1 = s[0];
    }

	static std::string fields()
	{
        return "id,name1,name3";
	}

	static std::string table()
	{
        return "User";
	}
};
struct User
{
    bool valid;
    unsigned long id;
    Person person;
    std::string name; //person name

    User() = default;
    User(const char** s)
    {
        name = s[0];
    }
    User(cave::Row<char,cave::mmsql::Data> s)
    {
        name = s[0];
    }


	static std::string fields()
	{
        return "id,person,name";
	}

	static std::string table()
	{
        return "User";
	}
};

class Login : public Gtk::Dialog
{
public:

	Login();
	Login(const Glib::ustring& title, Gtk::Window& parent, bool modal);
	void init();
	virtual ~Login();

	//int run();
	void set_session(const char*,const char*);
	const User& get_user()const;

protected:
	Gtk::Label lbMessage;
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	void on_response(int);

private:
	//int retcode;
	Gtk::Button btOK;
	Gtk::Button btCancel;
	Gtk::Entry inUser,inPwd;
	Gtk::Label lbUser,lbPass;
	Gtk::Box boxUser,boxPass;
	Gtk::ButtonBox boxButtons;
	User actual_user;

	void check_user();

};


class Main : public Gtk::Window
{
public:
	Main();
	Main(bool devel);
	/**
	*
	**/
	virtual ~Main();

	void set_title(const char* );
	void set_subtitle(const char* );
	void add_activity(Gtk::Widget&);
	const User& get_user()const;


	//const muposysdb::User& get_user() const;

protected:
	Gtk::HeaderBar header;
	Gtk::Toolbar tbMain;
	Gtk::Notebook nbMain;

	void init();
	virtual void check_session();
	virtual void notific_session();

#ifdef MUPOSYS_DESK_ENABLE_TDD
	//bool on_key_press_event(GdkEventKey* key_event) override;
#endif

private:
	Login login;
	Gtk::Label lbUser;
	bool devel;
	Gtk::VBox boxSlices;
	//Gtk::Button btUserMang;
	Gtk::Button btHome,btSysMang,btLogout,btAbout;
	Gtk::HBox box_header;
	Gtk::HBox box_header_info;
	Gtk::HBox box_header_controls;
	Gtk::Separator sep_header;

#ifdef MUPOSYS_DESK_ENABLE_TDD
	//TableSaling sales;
	Gtk::ToolButton btSales;
#endif
};

class Restaurant : public Main
{
public:
	/**
	*
	**/
	Restaurant();
	Restaurant(bool devel);
	virtual ~Restaurant();

protected:

private:

};

}

#endif
