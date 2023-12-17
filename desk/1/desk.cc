
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

#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
    #include <iostream>
#endif // OCTETOS_MUPOSYS_DESK_V1_TDD

#include "desk.hh"

namespace oct::mps::v1
{
    Application::Application() :
        header(NULL),
        boxSlices(NULL),
        boxToolbars(NULL),
        menu(NULL),
        stack(NULL)
    {
        init_data();
    }
    Application::Application(const Configuration& c) :
        config(c),
        header(NULL),
        boxSlices(NULL),
        boxToolbars(NULL),
        menu(NULL),
        stack(NULL)
    {
        init_data();
    }
    Application::Application(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
        Gtk::Window(cobject),
        header(NULL),
        boxSlices(NULL),
        boxToolbars(NULL),
        menu(NULL),
        stack(NULL)
    {
        init_controls(builder);
        init_data();
    }
    void Application::init_data()
    {
        set_default_size(config.width, config.height);
        set_title(config.title);
    }
    void Application::init_controls(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        builder->get_widget("header", header);
        header->set_show_close_button(true);
        set_titlebar(*header);
        header->set_subtitle(config.subtitle);

        //
        builder->get_widget("boxSlices", boxSlices);
    }


    Gtk::MenuBar& Application::get_menus()
    {
        return *menu;
    }
    Gtk::Box& Application::get_toolbar()
    {
        return *boxToolbars;
    }
    Gtk::Stack& Application::get_stack()
    {
        return *stack;
    }


    Application::Configuration::Configuration() : layout(Application::Layout::compressed),main_menu(false),status_bar(false),title("Multi-Porpuse Software System"),subtitle("muposys"),width(800),height(600)
    {
    }


}

