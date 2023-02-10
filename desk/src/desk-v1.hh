
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
    #include <muposys/core/Exception.hh>
    #include <cave/maria.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <muposys/core/src/Exception.hh>
    #include <cave/src/maria.hh>
#else
	#error "Plataforma desconocida."
#endif

//#include "TableSaling.hh"

namespace mps::v1
{

struct User
{
    long person;
    std::string name;

    User() = default;
    User(const char** r)
    {
        person = oct::core::atoi<long>(r[0]);
        name = r[1];
    }
};
struct Person
{
    std::string name1,name3;

    Person() = default;
    Person(const char** r)
    {
        name1 = r[0];
        name3 = r[1];
    }
};



class Login : public Gtk::Dialog
{
public:
    static const int NONE = 0;
    static const int CANCEL = 1;
    static const int OK = 2;
public:
	struct Credential
	{
		bool valid;
		std::string user; //user name
		std::string name; //person name
		User userdb;
	};
	Login();
	Login(const Glib::ustring& title, Gtk::Window& parent, bool modal);
	void init();
	virtual ~Login();

	int run();
	const Credential& get_credential() const;
	void set_session(const char*,const char*);

protected:
	Gtk::Label lbMessage;
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	void on_response(int);

private:
	//int retcode;
	Gtk::Box childs;
	Gtk::Button btOK;
	Gtk::Button btCancel;
	Gtk::Entry inUser,inPwd;
	Gtk::Label lbUser,lbPass;
	Gtk::Box boxUser,boxPass;
	Gtk::Box boxButtons;

	bool check_user();
	Credential credential;
};


class Main : public Gtk::ApplicationWindow
{
public:
    class Title : public Gtk::Box
    {
    public:
        Title();
        Title(const Glib::ustring& t);
        Title(const Glib::ustring& t, const Glib::ustring& st);

    private:
        void init();

    private:
        Gtk::Label title,subtitle;
    };

public:
	Main();
	Main(bool devel);
	/**
	*
	**/
	virtual ~Main();

	//void set_title(const char* );
	//void set_subtitle(const char* );
	void add_activity(Gtk::Widget&);

	//static Login::Credential credential;

	const User& get_user() const;
	const Glib::ustring& get_title()const;

protected:
	Gtk::HeaderBar header;
	//Gtk::Toolbar tbMain;
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
	Gtk::Box boxSlices;
	//Gtk::Button btUserMang;
	Gtk::Button btHome,btSysMang,btLogout,btAbout;
	Gtk::Box box_header;
	Gtk::Box box_header_info;
	Gtk::Box box_header_controls;
	Gtk::Separator sep_header;
    //Title title;
    Glib::ustring title;

#ifdef MUPOSYS_DESK_ENABLE_TDD
	//TableSaling sales;
	//Gtk::ToolButton btSales;
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
