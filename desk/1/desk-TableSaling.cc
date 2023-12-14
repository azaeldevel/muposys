
#include <iostream>

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
        add(cost_unit);
        add(amount);
    }

    void TableSaling::row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
    {
        //Gtk::TreeModel::Row row = *iter;

        //std::cout << "Size : " << tree_model->children().size() << "\n";
        const Gtk::TreeModel::iterator& last = --(tree_model->children().end());

        if(last == iter and crud == Crud::create) newrow();

        lbTotalAmount.set_text(std::to_string(total()));

        saved = false;
    }

    void TableSaling::newrow()
    {
        tree_model->append();
        Gtk::TreeModel::iterator& end = --tree_model->children();
        Gtk::TreeModel::Row row = *end;
        row[columns->itemDB] = NULL;
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

        table.set_model(tree_model);

        if(crud == Crud::create)
        {
            table.append_column_editable("Number", columns->number);
            Gtk::CellRendererText* cell_number = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(0));
            cell_number->property_editable() = true;
            cell_number->signal_editing_started().connect(sigc::mem_fun(*this, &TableSaling::on_editing_started_number));
            cell_number->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::on_edited_number));
            tree_model->signal_row_changed().connect(sigc::mem_fun(*this, &TableSaling::row_changed));
            table.append_column_editable("Cant.", columns->quantity);
            Gtk::CellRendererText* cell_quantity = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(table.get_n_columns() - 1));
            cell_quantity->property_editable() = true;
            table.append_column("Present.", columns->presentation);
            table.append_column_numeric_editable("C/U", columns->cost_unit,"%.2f");
            table.append_column_numeric_editable("Monto", columns->amount,"%.2f");

        }
        else
        {
            table.append_column("Number", columns->number);
            table.append_column("Cant.", columns->quantity);
            table.append_column("Present.", columns->presentation);
            table.append_column_numeric("C/U", columns->cost_unit,"%.2f");
            table.append_column_numeric("Monto", columns->amount,"%.2f");
        }
    }

    void TableSaling::on_editing_started_number(Gtk::CellEditable* editable, const Glib::ustring& path)
    {
        //std::cout << path << "||\n";
    }

    void TableSaling::on_edited_number(const Glib::ustring& path_string, const Glib::ustring& strnumb)
    {
        std::vector<Glib::ustring> res;
        if(split(strnumb,res))
        {
            std::cout << res[0] << "-" << res[1] << "<<\n";
        }
        else
        {
            std::cout << strnumb << "<<\n";
        }


    }
    bool TableSaling::on_key_press_event(GdkEventKey* event)
    {
        //std::cout << "on_key_press_event mias\n";
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
                    cave0::mmsql::Connection connDB;
                    cave0::mmsql::Data dtm = default_dtm0();
                    try
                    {
                        connDB_flag = connDB.connect(dtm, true);
                    }
                    catch (const cave0::ExceptionDriver& e)
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
                    catch (const cave0::ExceptionDriver& e)
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
                        if(row[columns->itemDB]) delete row[columns->itemDB];
                        else row[columns->itemDB] = new CatalogItem(lstItem[0]);
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
        else if ((event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_KP_Enter) or (event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_Return))
        {
            std::cout << ">>>pppppppppppppppppp<<<\n";
            Glib::RefPtr<Gtk::TreeSelection> refSelection = table.get_selection();
            Gtk::TreeModel::iterator iter = refSelection->get_selected();
            if(iter) //If anything is selected
            {
                Gtk::TreeModel::Row row = *iter;
                std::cout << row[columns->number] << "<<<\n";
            }

        }

        return true;
    }

    void TableSaling::set_data(Gtk::TreeModel::Row& row,const CatalogItem& item)
    {
        row[columns->item] = item.id;
        row[columns->number] = item.number;
        row[columns->cost_unit] = item.value;
        row[columns->presentation] = item.presentation;
        row[columns->amount] = row[columns->quantity] * row[columns->cost_unit];
    }




    bool TableSaling::split(const Glib::ustring& number,std::vector<Glib::ustring>& numbers)
    {
        //std::cout << "TableSaling::split : number " << number << "\n";
        Glib::ustring::size_type found = std::string(number).find("/");
        //std::cout << "TableSaling::split : found " << found << "\n";
        if(found != Glib::ustring::npos)
        {
            //std::cout << "TableSaling::split : combinada " << number << "\n";
            if(numbers.size() < 2) numbers.resize(2);
            numbers[0] = number.substr(0,found);
            numbers[1] = number.substr(found + 1, number.length() - 1);
            return true;
        }

        return false;
    }

}
