
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

#include <muposys/core/1/core.hh>

#ifdef OCTETOS_MUPOSYS_DESK_V2_TDD
    #include <iostream>
#endif // OCTETOS_MUPOSYS_DESK_V1_TDD

#include "desk.hh"

namespace oct::mps::v2
{
    Application::Application()
    {
        init();
    }
    Application::Application(const Configuration& c) : config(c)
    {
        init();
    }
    Application::Application(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Window(cobject)
    {

    }
    void Application::init()
    {
        set_title(config.title);
        set_default_size(config.width, config.height);
        box_app.set_homogeneous(false);
        box_menus.set_homogeneous(false);
        box_toolbars.set_homogeneous(false);
        box_app.set_orientation(Gtk::Orientation::VERTICAL);
        set_child(box_app);

        switch(config.layout)
        {
        case Application::Layout::compressed:
            box_app.append(box_menus);
            box_app.append(box_toolbars);
            box_app.append(switcher);
            switcher.set_stack(stack);
            box_app.append(stack);
            box_app.append(status);
            break;
        default:
            throw core::exception("El layout asignado es deconoconido");
        }

    }


    Gtk::Box& Application::get_menus()
    {
        return box_menus;
    }
    Gtk::Box& Application::get_toolbar()
    {
        return box_toolbars;
    }
    Gtk::Stack& Application::get_stack()
    {
        return stack;
    }


    Application::Configuration::Configuration() : layout(Application::Layout::compressed),main_menu(false),status_bar(false),title("Multi-Porpuse Software System"),subtitle("muposys"),width(800),height(600)
    {
    }

}

