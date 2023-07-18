
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


#ifdef __linux__

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida."
#endif


namespace mps::v1::gtk
{
    class Login : public Gtk::Dialog
    {
    public:
        Login();

    private:
        Gtk::Button btOK;
        Gtk::Button btCancel;
        Gtk::Entry inUser,inPwd;
        Gtk::Label lbUser,lbPass;
        Gtk::Box boxUser,boxPass;
        Gtk::ButtonBox boxButtons;
    };

    class Sales : public Gtk::Window
    {
    public:
        Sales() = default;

    private:

    };

    class Main : public Gtk::Window
    {
    public:
        Main();

        void on_login();

    private:
        Gtk::HeaderBar header;
        bool login;
        Login l;

    };
}

#endif
