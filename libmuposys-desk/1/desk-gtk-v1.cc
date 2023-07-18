
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


#include "desk-gtk-v1.hh"

#ifdef __linux__

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida."
#endif


namespace mps::v1::gtk
{
    Login::Login()
    {
        set_title("Inicio de Session");
        set_default_size(250, 100);
        set_hide_on_close();


    }



    Main::Main() : login(true)
    {
        header.set_show_title_buttons();
        set_titlebar(header);

        set_title("Multi-Porpuse Software System");
        set_default_size(800, 640);
        signal_show().connect(sigc::mem_fun(*this, &Main::on_login));

    }


    void Main::on_login()
    {
        l.set_transient_for(*this);
        l.set_modal();
        l.show();
    }
}

