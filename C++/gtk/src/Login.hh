#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH

/**
 *
 *  This file is part of muposys.
 *  muposys is a Multi-Porpuse Software System GUI.
 *  Copyright (C) 2018  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#include <gtkmm.h>

namespace muposys
{

class Login : public Gtk::Window
{
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Entry* txUser;
	Gtk::Entry* txPassword;
	Gtk::Label* lbMessage;
	Gtk::Button* btAccept;
	Gtk::Button* btCancel;
    //signal handlers
    void on_accept_button_clicked();
    void on_cancel_button_clicked();

public:
	Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
};

}
#endif