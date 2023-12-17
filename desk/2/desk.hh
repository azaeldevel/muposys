
#ifndef OCTETOS_MUPOSYS_DESK_V2_HH
#define OCTETOS_MUPOSYS_DESK_V2_HH

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

namespace oct::mps::v2
{

    class Sales : public Gtk::Box
    {

    };

    class Application : public Gtk::Window
    {
    public:
        enum class Layout
        {
            none,
            client_only,
            compressed,//toolbar y area de cliente
            sandwich,//area cliente en 3 sub-areas
            glade,
        };
        struct Configuration
        {
            Layout layout;
            bool main_menu;
            bool status_bar;
            Glib::ustring title,subtitle;
            int width,height;

            Configuration();
        };
    public:
      Application();
      Application(const Configuration& config);
      Application(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);

      Gtk::Box& get_menus();
      Gtk::Box& get_toolbar();
      Gtk::Stack& get_stack();

    protected:

    private:
        Configuration config;
        Gtk::Box box_app,box_toolbars,box_menus;
        Gtk::Stack stack;
        Gtk::StackSwitcher switcher;
        Gtk::Statusbar status;

    private:
      inline void init();

    };
}

namespace mps2 = oct::mps::v2;

#endif
