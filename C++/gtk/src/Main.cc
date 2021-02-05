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



#include "muposysdb.hpp"
#include "Main.hh"
#include "Login.hh"
#include "constants.h"
namespace muposys
{

AboutDialog::AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{
	
}






	 
	 
Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	wndLogin = 0;
	builder->get_widget_derived("wndLogin", wndLogin);
	wndLogin->show();

	set_title(title_window());
}

bool Main::on_button_press(GdkEventButton* event)
{
	//gtk_window_set_position ((GtkWindow*)GTK_WIDGET(event->window), GTK_WIN_POS_CENTER);
	return true;
}

const char* Main::title_window()const
{
	return MIPOSYS_NAME_FULL;
}

}