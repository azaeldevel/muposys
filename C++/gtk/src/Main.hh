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
		class Tools : public std::vector<Gtk::Widget*>
		{
		private:
			Gtk::MenuBar* mnbMain;
			Gtk::MenuItem* mniAbout;
			AboutDialog* dlgAbout;
			Gtk::Box* box;
			const Glib::RefPtr<Gtk::Builder>& builder;
		protected:
			void about_display();
		public:
			Tools(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		};
		
		class ActivityArea
		{
		private:
			Gtk::Viewport* vwpWork;
			Gtk::Fixed* fxWork;
			std::vector<Gtk::Widget*> tools;
			const Glib::RefPtr<Gtk::Builder>& builder;
			
		public:
			ActivityArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		};
		
		class Activity
		{
		protected:
			Tools* tools;
			ActivityArea* area;	
			const Glib::RefPtr<Gtk::Builder>& builder;
			
		public:	
			Activity(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		};

		class Activities : public std::stack<Activity*>
		{
		private:
			const Glib::RefPtr<Gtk::Builder>& builder;
			
		public:
			Activities(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		};
		
		/**
		*
		**/
		Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
		
	private:
		const Glib::RefPtr<Gtk::Builder> builder;
		Login* wndLogin;
		Activities activities;
		Activity* activityActual;	
		Tools tools;	
	};


}
#endif 
