
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
    Saling::Saling() : table(NULL),crud(Crud::none),cellrender_number(NULL)
    {
    }
    Saling::Saling(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Box(cobject),table(NULL),crud(Crud::none),cellrender_number(NULL)
    {
        init_controls(builder);
    }
    Saling::Saling(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder,Crud c) : Gtk::Box(cobject),table(NULL),crud(c),cellrender_number(NULL)
    {
        init_controls(builder);
    }
    void Saling::init_controls(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        int celrender_index_number;
        builder->get_widget("SalingTree", table);
        table_model = Gtk::TreeStore::create(model);
        table->set_model(table_model);
        table->set_activate_on_single_click(true);

        if(crud == Crud::create)
        {
            celrender_index_number = table->append_column_editable("Numero", model.number);
            //col_number = table->get_column(celrender_index_number - 1);
            //col_number->set_cell_data_func(*cellrender_number,sigc::mem_fun(*this,&Saling::on_column_editing_number));
            cellrender_number = static_cast<Gtk::CellRendererText*>(table->get_column_cell_renderer(celrender_index_number - 1));
            cellrender_number->property_editable() = true;
            //cellrender_number->signal_editing_started().connect(sigc::mem_fun(*this,&Saling::on_cell_editing_started));
            cellrender_number->signal_edited().connect(sigc::mem_fun(*this,&Saling::on_cell_edited));
            table->append_column_editable("Cant.", model.amount);
            table->append_column("Costo", model.cost);
            table->append_column("Total", model.total);
        }
        else
        {
            table->append_column("Numero", model.number);
            table->append_column("Cant.", model.amount);
            table->append_column("Costo", model.cost);
            table->append_column("Total", model.total);
        }
        table->signal_row_activated().connect(sigc::mem_fun(*this, &Saling::on_row_activated));
        table->signal_key_release_event().connect(sigc::mem_fun(*this, &Saling::keypress));
        //table_model->signal_row_changed().connect(sigc::mem_fun(*this, &Saling::on_row_changed));
        table_model->append();
        table_model->append();
        table_model->append();
    }

    void Saling::on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
    {
        //Gtk::TreeModel::iterator iter = table_model->get_iter(path);
        /*if(iter)
        {
            Gtk::TreeModel::Row row = *iter;
        }*/
        //path_last_actived = path;

        table->set_cursor(path,*column);
        std::cout << "Activando cell\n";
    }
    void Saling::on_row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
    {
        //Gtk::TreeModel::iterator iter = table_model->get_iter(path);
        /*if(iter)
        {
            Gtk::TreeModel::Row row = *iter;
        }*/
        //path_last_actived = path;
    }
    void Saling::on_cell_editing_started(Gtk::CellEditable* cell, const Glib::ustring& path)
    {
        auto entry = dynamic_cast<Gtk::Entry*>(cell);
        if(entry)
        {
            std::cout << entry->get_text() << "\n";
        }
    }
    void Saling::on_cell_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
    {
        std::cout << path_string << ":" << new_text << "\n";
    }
    void Saling::on_column_editing_number(Gtk::CellRenderer* cell, const Gtk::TreeModel::iterator& iter)
    {
        auto entry = dynamic_cast<Gtk::Entry*>(cell);
        if(entry)
        {
            std::cout << entry->get_text() << "\n";
        }
    }
    bool Saling::keypress(GdkEventKey* key_event)
    {
        std::cout << "keypress : " << (char)key_event->keyval << "\n";
        return false;
    }

    Saling::Model::Model()
    {
        add(number);
        add(amount);
        add(cost);
        add(total);
    }




    Application::Application()
    {
        init_data();
    }
    Application::Application(const Configuration& c) : config(c)
    {
        init_data();
    }
    Application::Application(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) : Gtk::Window(cobject)
    {
        init_controls(builder);
        init_data();
    }
    void Application::init_data()
    {
        set_default_size(config.width, config.height);
        set_title(config.title);
        status->push("inicializando applicacion...");
    }
    void Application::init_controls(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        header = NULL;
        boxSlices = NULL;
        boxToolPane = NULL;
        menu = NULL;
        stack = NULL;
        status = NULL;

        builder->get_widget("header", header);
        header->set_show_close_button(true);
        set_titlebar(*header);
        header->set_subtitle(config.subtitle);

        //
        builder->get_widget("boxSlices", boxSlices);

        //
        builder->get_widget("menu", menu);
        builder->get_widget("status", status);
        builder->get_widget("stack", stack);
        builder->get_widget("boxToolPane", boxToolPane);




        //
        Saling *saling = NULL;
        builder->get_widget_derived("Saling", saling,Crud::create);
        stack->add(*saling,std::to_string((long)saling),"Ventas - Caja 1");
        /*Saling *saling2 = NULL;
        builder->get_widget_derived("Saling", saling2);
        stack->add(*saling2,"page1","Venta - Caja 2");*/
    }


    Gtk::MenuBar& Application::get_menus()
    {
        return *menu;
    }
    Gtk::Box& Application::get_toolpane()
    {
        return *boxToolPane;
    }
    Gtk::Stack& Application::get_stack()
    {
        return *stack;
    }


    Application::Configuration::Configuration() : layout(Application::Layout::compressed),main_menu(false),status_bar(false),title("Multi-Porpuse Software System"),subtitle("muposys"),width(800),height(600)
    {
    }




}

