
#ifndef MUPOSYS_SPLASH_HH
#define MUPOSYS_SPLASH_HH

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
#include <glibmm/i18n.h>
#include <gtkmm.h>

#ifdef __linux__
    #include <muposys/core/Exception.hh>
    #include <cave/maria.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <muposys/core/src/Exception.hh>
    #include <cave/src/maria.hh>
#else
	#error "Plataforma desconocida."
#endif

//#include "TableSaling.hh"

namespace mps::v1
{


class Splash : public Gtk::Window
{
public:
    Splash();
    void init();

private:
    Gtk::Label message;
    Gtk::Box controls;
};


}

#endif
