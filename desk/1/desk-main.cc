
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

#include "desk.hh"

namespace mps = oct::mps::v1;

int main (int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "octetos.muposys.desk");

    //Load the Glade file and instantiate its widgets:
    auto refBuilder = Gtk::Builder::create();
    try
    {
#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
        refBuilder->add_from_file("1/muposys.glade");
#else
        refBuilder->add_from_file("muposys.glade");
#endif
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    mps::Application* pApp = NULL;
  try
  {
    refBuilder->get_widget_derived("Application", pApp);
    if(pApp) app->run(*pApp);
  }
  catch(const std::exception& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const mps::core::exception& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  //Get the GtkBuilder-instantiated dialog:
  delete pApp;

  return 0;
}
