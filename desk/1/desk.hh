
#ifndef OCTETOS_MUPOSYS_DESK_V1_HH
#define OCTETOS_MUPOSYS_DESK_V1_HH

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

#include <muposys/core/1/core.hh>

namespace oct::mps::v1
{
    class Main;

    namespace cave = oct::cave::v0;

    class TableSaling : public Gtk::VBox
    {
    public:
        TableSaling();
        TableSaling(ID);

    };

    class Login : public Gtk::Dialog
    {
    public:
        typedef sigc::signal<void> signal_logged_t;

    public:
        signal_logged_t signal_logged();

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
        signal_logged_t _signal_logged;

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
        void on_logged();
        template<typename F> void on_logged_listener(F f)
        {
            login.signal_logged().connect(f);
        }

    protected:
        Gtk::HeaderBar header;
        Gtk::Toolbar tbMain;
        Gtk::Notebook nbMain;

        void init();
        virtual void check_session();
        //virtual void notific_session();

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
