
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


#include "splash-v1.hh"

#ifdef __linux__
	#include "config.h"
#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida."
#endif


namespace mps::v1
{
Splash::Splash() : controls(Gtk::Orientation::VERTICAL)
{
    init();
}

void Splash::init()
{
    set_child(controls);
    controls.prepend(message);
    message.set_text("Iniciando...");
    //set_decorated(false);
    //show_all();
}











}

