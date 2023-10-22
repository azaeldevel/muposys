

#include "desk.hh"


namespace oct::mps::v1
{
    TableSaling::TableSaling() : connDB_flag(false),notebook(NULL),notebook_page_index(0),crud(Crud::create),order(-1)
    {
        //std::cout << "mps::TableSaling::TableSaling()\n";
        init();
    }
    TableSaling::TableSaling(ID o) : connDB_flag(false),notebook(NULL),notebook_page_index(0),crud(Crud::read),order(o)
    {
        //std::cout << "mps::TableSaling::TableSaling(long)\n";
        init();
    }
    TableSaling::TableSaling(ID o,Crud c) : connDB_flag(false),notebook(NULL),notebook_page_index(0),crud(c),order(o)
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

            tree_model = Gtk::ListStore::create(columns);
            tree_model->signal_row_changed().connect(sigc::mem_fun(*this, &TableSaling::row_changed));
            table.set_model(tree_model);

            if(crud == Crud::create) table.append_column_editable("Cant.", columns.quantity);
            else table.append_column("Cant.", columns.quantity);
            Gtk::CellRendererText* cell_quantity = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(table.get_n_columns() - 1));
            //Gtk::TreeViewColumn* col_quantity = table.get_column(table.get_n_columns() - 1);
            if(crud == Crud::create) cell_quantity->property_editable() = true;

            table.append_column("Present.", columns.presentation);

            if(crud == Crud::create)table.append_column_editable("Number", columns.number);
            else table.append_column("Number", columns.number);

            table.append_column("Artículo", columns.name);

            if(crud == Crud::create) table.append_column_numeric_editable("C/U", columns.cost_unit,"%.2f");
            else table.append_column_numeric("C/U", columns.cost_unit,"%.2f");

            if(crud == Crud::create)table.append_column_numeric_editable("Monto", columns.amount,"%.2f");
            else table.append_column_numeric("Monto", columns.amount,"%.2f");
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

        if(crud == Crud::create) newrow();
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
    void TableSaling::row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
    {
        //Gtk::TreeModel::Row row = *iter;

        //std::cout << "Size : " << tree_model->children().size() << "\n";
        const Gtk::TreeModel::iterator& last = --(tree_model->children().end());

        if(last == iter and crud == Crud::create) newrow();

        lbTotalAmount.set_text(std::to_string(total()));
        //if(notebook) mark_unsave();

        saved = false;
    }
    void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text)
    {

    }

    void TableSaling::newrow()
    {
        *tree_model->append();
    }

    float TableSaling::total() const
    {
        Gtk::TreeModel::Row row;
        float tt = 0;
        for(const Gtk::TreeModel::iterator& it : tree_model->children())
        {
            row = *it;
            tt += row[columns.amount];
        }
        return tt;
    }


    void TableSaling::clear()
    {
        tree_model->clear();
        lbTotalAmount.set_text("");
        newrow();
    }
    void TableSaling::mark_unsave()
    {
        if(not saved) return;//ya esta marcado como no guardado

        if(notebook)
        {
            //std::cout << "Sin guardar\n";
            if(notebook_page_index < 0) return; //no is a child of nb.
            Widget* page = notebook->get_nth_page(notebook_page_index);
            Glib::ustring text = notebook->get_tab_label_text(*page);
            notebook->set_tab_label_text(*page,text + "*");
        }
        else //if other type parent
        {
            Gtk::MessageDialog dlg("Error Interno",true,Gtk::MESSAGE_ERROR);
            dlg.set_secondary_text("No se reconoce el tipo de contenedor.");
            dlg.run();
        }
    }
    void TableSaling::set_info(Gtk::Notebook& parent,int page_index)
    {
        notebook = &parent;
        notebook_page_index = page_index;
    }
    void TableSaling::save()
    {
    }









}
