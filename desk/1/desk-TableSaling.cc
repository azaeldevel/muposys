

#include "desk.hh"


namespace oct::mps::v1
{
    TableSaling::TableSaling() : connDB_flag(false),crud(Crud::create),order(-1),columns(NULL)
    {
        //std::cout << "mps::TableSaling::TableSaling()\n";
        init();
    }
    TableSaling::TableSaling(ID o) : connDB_flag(false),crud(Crud::read),order(o),columns(NULL)
    {
        //std::cout << "mps::TableSaling::TableSaling(long)\n";
        init();
    }
    TableSaling::TableSaling(ID o,Crud c) : connDB_flag(false),crud(c),order(o),columns(NULL)
    {
        //std::cout << "mps::TableSaling::TableSaling(long)\n";
        init();
    }
    void TableSaling::init()
    {
        set_valign(Gtk::ALIGN_CENTER);
        table.add_events(Gdk::KEY_PRESS_MASK);
        pack_start(table,false,true);//
        {
            set_homogeneous(false);
        }

        pack_start(separator,false,true,5);

        pack_start(boxAditional,false,true);

        pack_start(boxFloor,false,true,5);
        {
            //agregando widgets de total
            boxFloor.pack_start(boxTotal);
            {
                boxTotal.pack_start(lbTotal);
                boxTotal.pack_start(lbTotalAmount);
                lbTotal.set_text("Total : $");
            }
    /*#ifdef OCTETOS_MUPOSYS_DESK_V1_TDD
            btSave.signal_clicked().connect( sigc::mem_fun(*this,&TableSaling::on_save_clicked));
    #endif*/
            btSave.set_image_from_icon_name("document-save");
            boxFloor.pack_start(btSave,Gtk::PACK_SHRINK);
        }

        saved = true;

        //if(crud == Crud::create) newrow();
    }
    TableSaling::~TableSaling()
    {
    }
    TableSaling::ModelColumns::ModelColumns()
    {
        //add(id);
        add(item);
        add(quantity);
        add(presentation);
        add(number);
        add(name);
        add(cost_unit);
        add(amount);
    }
    /*void TableSaling::row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
    {
        //Gtk::TreeModel::Row row = *iter;

        //std::cout << "Size : " << tree_model->children().size() << "\n";
        const Gtk::TreeModel::iterator& last = --(tree_model->children().end());

        if(last == iter and crud == Crud::create) newrow();

        lbTotalAmount.set_text(std::to_string(total()));

        saved = false;
    }*/

    void TableSaling::newrow()
    {
        tree_model->append();
    }

    float TableSaling::total() const
    {
        Gtk::TreeModel::Row row;
        float tt = 0;
        for(const Gtk::TreeModel::iterator& it : tree_model->children())
        {
            row = *it;
            tt += row[columns->amount];
        }
        return tt;
    }


    void TableSaling::clear()
    {
        tree_model->clear();
        lbTotalAmount.set_text("");
        newrow();
    }

    void TableSaling::save()
    {
    }

    void TableSaling::init_table()
    {
        if(not columns) return;

        //tree_model->signal_row_changed().connect(sigc::mem_fun(*this, &TableSaling::row_changed));
        table.set_model(tree_model);

            if(crud == Crud::create) table.append_column_editable("Cant.", columns->quantity);
            else table.append_column("Cant.", columns->quantity);
            Gtk::CellRendererText* cell_quantity = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(table.get_n_columns() - 1));
            //Gtk::TreeViewColumn* col_quantity = table.get_column(table.get_n_columns() - 1);
            if(crud == Crud::create) cell_quantity->property_editable() = true;

            table.append_column("Present.", columns->presentation);

            if(crud == Crud::create)table.append_column_editable("Number", columns->number);
            else table.append_column("Number", columns->number);

            table.append_column("Artículo", columns->name);

            if(crud == Crud::create) table.append_column_numeric_editable("C/U", columns->cost_unit,"%.2f");
            else table.append_column_numeric("C/U", columns->cost_unit,"%.2f");

            if(crud == Crud::create)table.append_column_numeric_editable("Monto", columns->amount,"%.2f");
            else table.append_column_numeric("Monto", columns->amount,"%.2f");
    }


    bool TableSaling::on_key_press_event(GdkEventKey* event)
    {
        //std::cout << "on_key_press_event\n";
        if (event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_F4)
        {
            //std::cout << "on_key_press_event F4 begin\n";
            ID number;
            SearchItem search(number);
            if(search.run() == Gtk::RESPONSE_OK)
            {
                //std::cout << "number : " << number  << "\n";
                Glib::RefPtr<Gtk::TreeSelection> refSelection = table.get_selection();
                Gtk::TreeModel::iterator iter = refSelection->get_selected();
                if(iter) //If anything is selected
                {
                    cave::mmsql::Connection connDB;
                    cave::mmsql::Data dtm = default_dtm();
                    try
                    {
                        connDB_flag = connDB.connect(dtm, true);
                    }
                    catch (const cave::ExceptionDriver& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (const std::exception& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (...)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text("Error desconocido en la creacion de la conexion a la base de datos");
                        dlg.run();
                        return true;
                    }

                    Glib::ustring where;
                    where += "id = '" + std::to_string(number) + "'" ;
                    std::vector<CatalogItem> lstItem;
                    bool lstItemflag = false;
                    try
                    {
                         lstItemflag = connDB.select(lstItem,where);
                    }
                    catch (const cave::ExceptionDriver& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (const std::exception& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (...)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text("Error desconocido en la creacion de la conexion a la base de datos");
                        dlg.run();
                        return true;
                    }

                    if(lstItemflag and lstItem.size() == 1)
                    {
                        //std::cout << "writing in model..\n";
                        Gtk::TreeModel::Row row = *iter;
                        set_data(row,lstItem[0]);
                    }
                    else
                    {
                        Gtk::MessageDialog dlg("Deve seleccionar un item de la lista antes de continuar",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text("No hay seleccion.");
                        dlg.run();
                        return true;
                    }

                    connDB.close();
                }

            }
            else
            {

            }

        }

        return true;
    }

    void TableSaling::set_data(Gtk::TreeModel::Row& row,const CatalogItem& item)
    {
        row[columns->item] = item.id;
        row[columns->number] = item.number;
        row[columns->name] = "name";
        row[columns->cost_unit] = item.value;
        row[columns->presentation] = item.presentation;
        row[columns->amount] = row[columns->quantity] * row[columns->cost_unit];
    }





}
