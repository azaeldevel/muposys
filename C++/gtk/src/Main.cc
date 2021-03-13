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
#include "Catalog.hh"



namespace muposys
{

AboutDialog::AboutDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : builder(refGlade)
{
	
}






Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	set_title(titleWindow());
	builder->get_widget("tbrDocsSeller", tbrDocsSeller);
	builder->get_widget("tbrAdmin", tbrAdmin);
	//builder->get_widget("btUser", btUser);
	//builder->get_widget("btQuotation", btQuotation);
	builder->get_widget("lbUser", lbUser);
	builder->get_widget("lbSystem", lbSystem);
	lbSystem->set_text(systemName());
	signal_focus_in_event().connect(sigc::mem_fun(*this, &Main::on_windows_focus));
	btStockCatalog = 0;
	builder->get_widget("btStockCatalog", btStockCatalog);
	btStockCatalog->signal_clicked().connect(sigc::mem_fun(*this,&Main::on_btStockCatalog_clicked));
		
	wndLogin = 0;
	user = NULL;
	builder->get_widget_derived("wndLogin", wndLogin);
	wndLogin->linkUser(&user);
	wndLogin->show();
}
const char* Main::titleWindow()const
{
	return MIPOSYS_NAME_FULL;
}
const char* Main::systemName()const
{
	return MIPOSYS_NAME;
}


bool Main::on_button_press(GdkEventButton* event)
{
	return true;
}


bool Main::on_windows_focus(void* user_data)
{
	if(user != NULL)
	{
		std::string strname;
		if(!user->getPerson().getName1().empty()) strname += user->getPerson().getName1();
		strname += " ";
		if(!user->getPerson().getName3().empty()) strname += user->getPerson().getName3();
		strname += "(";
		strname += user->getName() + ")";
		lbUser->set_text(strname);
		//std::cout << "\n>>>>>>>>>>>>>lbUser->set_text(" << user->getName() << ")\n";
	}
	
	return true;
}
void Main::on_btStockCatalog_clicked()
{
	Catalog* wndCatalog = 0;
	builder->get_widget_derived("wndCatalog", wndCatalog);
	wndCatalog->show();
}
}