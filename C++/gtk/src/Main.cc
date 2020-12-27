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

namespace muposys
{

AboutDialog::AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{
	
}








	 

void Main::Tools::about_display()
{
	//dlgAbout = 0;
	//builder->get_widget_derived("dlgAbout", dlgAbout);
	//dlgAbout->show();
}
Main::Tools::Tools(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{
	builder->get_widget("mnbMain", mnbMain);
	builder->get_widget("mniAbout", mniAbout);
	mniAbout->signal_select().connect(sigc::mem_fun(*this, &Main::Tools::about_display));
}



	 




	 
Main::ActivityArea::ActivityArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{
	builder->get_widget("vwpWork", vwpWork);
	builder->get_widget("fxWork", fxWork);

	vwpWork->set_size_request(400,400);
}		 






	 

Main::Activity::Activity(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{
}






	 

Main::Activities::Activities(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{

}







	 
	 
Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) 
	: Gtk::Window(cobject), builder(refGlade),activities(cobject,refGlade),tools(cobject,refGlade)
{
	wndLogin = 0;
	builder->get_widget_derived("wndLogin", wndLogin);
	wndLogin->show();

	activityActual = new Activity(cobject,refGlade);
}


}