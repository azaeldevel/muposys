#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

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
#include <stack>


#include "Login.hh"

namespace muposys
{

	class AboutDialog : public Gtk::AboutDialog
	{
	private:
		const Glib::RefPtr<Gtk::Builder>& builder;

	public:
		AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	};

	class Main : public Gtk::Window
	{
	public:

		/**
		*
		**/
		Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);		
		bool on_button_press(GdkEventButton* event);		
		const char* titleWindow()const;
		const char* systemName()const;
		//carga de gui no gestionadna por glade
		
	protected:
		bool on_windows_focus(void* user_data);
		void on_btStockCatalog_clicked();
	private:
		const Glib::RefPtr<Gtk::Builder> builder;
		Login* wndLogin;
		Gtk::Toolbar* tbrDocsSeller;
		Gtk::Toolbar* tbrAdmin;
		Gtk::Button* btUser;
		Gtk::Button* btQuotation;
		Gtk::Label* lbUser;
		Gtk::Label* lbSystem;
		muposysdb::Users* user;
		std::string struser;
		Gtk::ToolButton* btStockCatalog;	
	};

}
#endif 
