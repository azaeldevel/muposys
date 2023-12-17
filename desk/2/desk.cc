
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
    void Application::init()
    {
        set_title(config.title);
        set_default_size(config.width, config.height);

    }



    Application::Configuration::Configuration() : layout(Application::Layout::sandwich),main_menu(false),status_bar(false),title("Multi-porpuse Software System"),subtitle("muposys"),width(800),height(600)
    {
    }

}

