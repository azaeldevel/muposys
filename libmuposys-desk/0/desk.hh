
#ifndef OCTETOS_MUPOSYS_DESK_V0_HH
#define OCTETOS_MUPOSYS_DESK_V0_HH

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
    #include <core/3/Exception.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <muposys/core/src/Exception.hh>
#else
	#error "Plataforma desconocida."
#endif

#include "TableSaling.hh"

namespace mps::v0
{
    class Main;

    struct Credential
	{
		bool valid;
		std::string user; //user name
		std::string name; //person name

	};

    class Login : public Gtk::Dialog
    {
    public:
        /**/
        Login(Main&);
        Login(const Glib::ustring& title, Gtk::Window& parent, bool modal,Main&);
        void init();
        virtual ~Login();

        const Credential& validating();
        void set_session(const char*,const char*);

    protected:

    protected:
        Gtk::Label lbMessage;
        void on_bt_ok_clicked();
        void on_bt_cancel_clicked();

    private:
        Gtk::Button *btOK,*btCancel;
        Gtk::Entry inUser,inPwd;
        Gtk::Label lbUser,lbPass;
        Gtk::Box boxUser,boxPass;

        Main* main;
        Credential credential;
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

        //void set_title(const char* );
        void set_subtitle(const char* );
        //void add_activity(Gtk::Widget&);

        //Credential credential;

        //const muposysdb::User& get_user() const;
        void login_check(const Credential&);
        void login_cancel();

    protected:
        Gtk::HeaderBar header;
        Gtk::Toolbar tbMain;
        Gtk::Notebook nbMain;

        void on_login();

    private:
        Login login;
        Gtk::Label lbUser;
        Gtk::VBox boxSlices;
        //Gtk::Button btUserMang;
        Gtk::Button btHome,btSysMang,btLogout,btAbout;
        Gtk::HBox box_header;
        Gtk::HBox box_header_info;
        Gtk::HBox box_header_controls;
        Gtk::Separator sep_header;

    private:
        void init();
#ifdef OCTETOS_MUPOSYS_DESK_TDD_V0
        //bool on_key_press_event(GdkEventKey* key_event) override;
    private:
        bool devel;
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
