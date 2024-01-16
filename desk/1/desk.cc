
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
        //int celrender_index_bief;
        builder->get_widget("SalingTree", table);
        table_model = Gtk::TreeStore::create(model);
        table->set_model(table_model);
        table->set_activate_on_single_click(true);

        if(crud == Crud::create)
        {
            celrender_index_number = table->append_column_editable("Numero", model.number);
            col_number = table->get_column(celrender_index_number - 1);
            //col_number->set_cell_data_func(*cellrender_number,sigc::mem_fun(*this,&Saling::on_column_editing_number));
            cellrender_number = dynamic_cast<Gtk::CellRendererText*>(table->get_column_cell_renderer(celrender_index_number - 1));
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
        //table->signal_row_activated().connect(sigc::mem_fun(*this, &Saling::on_row_activated));
        //table->signal_key_release_event().connect(sigc::mem_fun(*this, &Saling::keypress));
        //table_model->signal_row_changed().connect(sigc::mem_fun(*this, &Saling::on_row_changed));

        //table->set_enable_search(true);
        //table->set_search_column(*col_number);
        //inSearch = table->get_search_entry();
        //inSearch->signal_changed().connect(sigc::mem_fun(*this, &Saling::searching));

        table_model->append();
        table_model->append();

        table_model->append();
    }
    void Saling::on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
    {
        std::cout << "Actived : " << path[0] << "\n";

        path_actived = path;
    }
    bool Saling::keypress(GdkEventKey* key_event)
    {
        std::cout << "keypress : " << (char)key_event->keyval << "\n";
        //strsearch.insert(strsearch.size() - 1,(char)key_event->keyval);


        return false;
    }


    void Saling::on_row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
    {
        //Gtk::TreeModel::iterator iter = table_model->get_iter(path);
        /*if(iter)
        {
            Gtk::TreeModel::Row row = *iter;
        }*/
        std::cout << "Actived : " << path[0] << "\n";
    }
    void Saling::on_cell_editing_started(Gtk::CellEditable* cell, const Glib::ustring& path)
    {
        auto entry = dynamic_cast<Gtk::Entry*>(cell);
        if(entry)
        {
            std::cout << "Cell : " << entry->get_text() << "\n";
        }
    }
    void Saling::on_cell_edited(const Glib::ustring& path_string, const Glib::ustring& text)
    {
        //std::cout << path_string << ":" << new_text << "\n";

        cave::mmsql::Data dtm = default_dtm();
        bool conectfl = false;
        cave::mmsql::Connection conn;
        try
        {
            conectfl = conn.connect(dtm, true);
        }
        catch (const cave::ExceptionDriver& e)
        {
            std::cout << "Exception (cave testing) : " << e.what() << "\n";
            return;
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception (cave testing) : " << e.what() << "\n";
            return;
        }
        catch (...)
        {
            return;
        }
        if(not conectfl)
        {
            std::cout << "Fallo la conexion de la base de datos\n";
            return;
        }

        std::vector<CatalogItem> rs1;
        std::string where = "number = '";
        where += text + "'";
        try
        {
            conn.select(rs1,where.c_str());
            //std::cout << "Text : " << rs1[0].brief << "\n";
        }
        catch (const cave::ExceptionDriver& e)
        {
            std::cout << "Exception (cave testing) : " << e.what() << "\n";
            return;
        }
        catch (...)
        {
            return;
        }
    }
    void Saling::on_column_editing_number(Gtk::CellRenderer* cell, const Gtk::TreeModel::iterator& iter)
    {
        auto entry = dynamic_cast<Gtk::Entry*>(cell);
        if(entry)
        {
            std::cout << entry->get_text() << "\n";
        }
    }
    void Saling::searching()
    {
        //std::cout << "Searching : " << inSearch->get_text() << "\n";
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
        /*
        Saling *saling2 = NULL;
        builder->get_widget_derived("Saling", saling2);
        stack->add(*saling2,"page1","Venta - Caja 2");
        */

        login = NULL;
        builder->get_widget_derived("Login", login);
        signal_show().connect(sigc::mem_fun(*this,&Application::check_session));

        init_data();
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

    void Application::check_session()
    {
        login->set_transient_for(*this);
        login->set_modal(true);
        //if(devel) login.set_session("root","123456");
        login->show();
    }


    Application::Configuration::Configuration() : layout(Application::Layout::compressed),main_menu(false),status_bar(false),title("Multi-Porpuse Software System"),subtitle("muposys"),width(800),height(600)
    {
    }



    Login::Login(BaseObjectType* obj, const Glib::RefPtr<Gtk::Builder>& builder)  : Gtk::Dialog(obj)
    {
        init_controls(builder);
    }
    void Login::init_data()
    {
        set_title("Login");
        set_default_size(300, 150);

        btCancel->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_Cancel_clicked));
        btAccept->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_Accept_clicked));
        signal_response().connect(sigc::mem_fun(*this,&Login::on_response));
    }
    void Login::init_controls(const Glib::RefPtr<Gtk::Builder>& builder)
    {
        inUser = NULL;
        builder->get_widget("inUser", inUser);
        inPassword = NULL;
        builder->get_widget("inPassword", inPassword);
        btAccept = NULL;
        builder->get_widget("btAccept", btAccept);
        btCancel = NULL;
        builder->get_widget("btCancel", btCancel);
        infoLogin = NULL;
        builder->get_widget("infoLogin", infoLogin);

        init_data();
    }
    void Login::on_bt_Cancel_clicked()
    {
        response(Gtk::RESPONSE_CANCEL);
    }
    void Login::on_bt_Accept_clicked()
    {
        response(Gtk::RESPONSE_OK);
    }
    void Login::on_response(int res)
    {
        if(check(user))
        {
            hide();
        }
        else
        {
            //

        }
    }
    bool Login::check(User& u)
    {
        Configuration config;
        cave::mmsql::Data dtm;
        std::string name;
        try
        {
            config.open();
            name = config.get_name();
            //std::cout << "name : " << name << "\n";
            dtm = config.get_datasource();
            //std::cout << "host : " << dtm.get_host() << "\n";
        }
        catch (const cave::ExceptionDriver& e)
        {
            std::cout << "Exception: " << e.what() << "\n";
            return false;
        }
        catch (const core::exception& e)
        {
            std::cout << "Exception: " << e.what() << "\n";
            return false;
        }
        catch (const libconfig::SettingTypeException& e)
        {
            std::cout << "Exception: " << e.what() << "\n";
            return false;
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception: " << e.what() << "\n";
            return false;
        }
        catch (...)
        {
            return false;
        }

        //std::cout << "Conectando...\n";

        bool conectfl = false;
        cave::mmsql::Connection conn;
        try
        {
            conectfl = conn.connect(dtm, true);
        }
        catch (const cave::ExceptionDriver& e)
        {
            std::cout << "Exception (cave testing) : " << e.what() << "\n";
            return false;
        }
        catch (const std::exception& e)
        {
            std::cout << "Exception (cave testing) : " << e.what() << "\n";
            return false;
        }
        catch (...)
        {
            return false;
        }
        if(not conectfl)
        {
            std::cout << "Fallo la conexion de la base de datos\n";
            return false;
        }

        std::vector<User> rs1;
        std::string where;
        where += " name = '" + inUser->get_text() + "' and pwdtxt = '" + inPassword->get_text() + "' and status = 3";
        try
        {
            conn.select(rs1,where.c_str());
            //std::cout << "Text : " << rs1[0].brief << "\n";
        }
        catch (const cave::ExceptionDriver& e)
        {
            std::cout << "Exception (cave testing) : " << e.what() << "\n";
            return false;
        }
        catch (...)
        {
            return false;
        }

        if(rs1.size() == 1)
        {
            user = rs1[0];
            return true;
        }
        else
        {
            return false;
        }

        return false;
    }



}

