
#include "desk.hh"

namespace oct::mps::v1
{


    const Glib::ustring SearchItem::search_label = "Buscar...";

	SearchItem::SearchItem(ID& n) : number(n)
	{
		init();
	}
	void SearchItem::init()
	{
		number = -1;
        cave0::mmsql::Data dtm = default_dtm();
        try
        {
            connDB_flag = connDB.connect(dtm, true);
        }
        catch (const cave0::ExceptionDriver& e)
        {
            Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
            dlg.set_secondary_text(e.what());
            dlg.run();
            return;
        }
        catch (const std::exception& e)
        {
            Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
            dlg.set_secondary_text(e.what());
            dlg.run();
            return;
        }
        catch (...)
        {
            Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
            dlg.set_secondary_text("Error desconocido en la creacion de la conexion a la base de datos");
            dlg.run();
            return;
        }

		set_title(search_label);

		//
		treemodel = Gtk::ListStore::create(colums);
		tree.set_model(treemodel);
		tree.append_column("Número", colums.number);
		tree.append_column("Nombre", colums.name);
		tree.append_column("Descripcción", colums.brief);
		scrolled.add(tree);
		scrolled.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		get_vbox()->pack_start(scrolled);

		btCancel.signal_clicked().connect(sigc::mem_fun(*this,&SearchItem::on_bt_cancel_clicked));
		btOK.signal_clicked().connect(sigc::mem_fun(*this,&SearchItem::on_bt_ok_clicked));
		signal_response().connect(sigc::mem_fun(*this, &SearchItem::on_response));
		btOK.set_image_from_icon_name("gtk-ok");
		btCancel.set_image_from_icon_name("gtk-cancel");

		get_vbox()->pack_start(boxButtons,false,true);
		boxButtons.pack_start(btOK,false,true);
		boxButtons.pack_start(btCancel,false,true);

		set_default_size(340,200);
		show_all_children();
	}


	void SearchItem::on_bt_cancel_clicked()
	{
		response(Gtk::RESPONSE_CANCEL);
	}
	void SearchItem::on_bt_ok_clicked()
	{
		get_selection();
	}

	void SearchItem::on_response(int res)
	{
		if(res == Gtk::RESPONSE_OK)
		{
			hide();
		}
		else
		{
			switch (res)
			{
			case Gtk::RESPONSE_CLOSE:
			case Gtk::RESPONSE_CANCEL:
			case Gtk::RESPONSE_DELETE_EVENT:
				hide();
				break;
			}
		}
	}

	bool SearchItem::on_key_press_event(GdkEventKey* event)
	{
		if (event->keyval >= 97 and event->keyval <= 122)//letras minisculas
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval >= 65 and event->keyval <= 90)//letras mayusculas
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval == 32)//space
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval == 45)//gion
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval == GDK_KEY_Return)
		{
			//std::cout << "key : Enter\n";
			get_selection();
		}
		else if (event->keyval == GDK_KEY_Escape)
		{
			//std::cout << "key : Enter\n";
			text = "";
			set_title(search_label);
			treemodel->clear();
		}
		else if (event->keyval == GDK_KEY_BackSpace)
		{
			//std::cout << "key : Enter\n";
			Glib::ustring::iterator it = text.end();
			if(text.size() > 0)
			{
				--it;
				text.erase(it);
				set_title(search_label + " " + text);
				searching(text);
			}
			else if(text.size() == 0)
			{
				treemodel->clear();
			}

		}
		else
		{
			//std::cout << "key : " << event->keyval << "\n";
		}

		return false;
	}

    SearchItem::ModelColumns::ModelColumns()
    {
        add(id);
        add(number);
        add(name);
        add(brief);
    }

    void SearchItem::searching(const Glib::ustring& s)
    {
        //std::cout << "key : " << text << "\n";
        Glib::ustring where;
        where += "number LIKE '%";
        where += text + "%'";
        where += " or brief LIKE '%";
        where += text + "%'";
        where += " or name LIKE '%";
        where += text + "%'";
        where += " or size LIKE '%";
        where += text + "%'";
        //std::cout << "where : " << where << "\n";
        set_title(search_label + " " + text);
        //std::vector<muposysdb::CatalogItem*>* lstItem = muposysdb::CatalogItem::select(connDB,where);
        std::vector<CatalogItem> lstItem;
        bool lstItemflag = false;
        try
        {
             lstItemflag = connDB.select(lstItem,where);
        }
        catch (const cave0::ExceptionDriver&)
        {
        }
        catch (...)
        {
        }

        if(lstItemflag)
        {
            Gtk::TreeModel::Row row;
            treemodel->clear();
            //std::cout << "i : " << lstItem->size() << "\n";
            for(size_t i = 0; i < lstItem.size(); i++)
            {
                row = *(treemodel->append());
                row[colums.id] = lstItem[i].id;
                row[colums.number] = lstItem[i].number;
                row[colums.name] = "nombre";
                row[colums.brief] = lstItem[i].brief;
            }
        }
    }
    void SearchItem::get_selection()
    {
        Glib::RefPtr<Gtk::TreeSelection> refSelection = tree.get_selection();
        Gtk::TreeModel::iterator iter = refSelection->get_selected();
        if(iter) //If anything is selected
        {
            Gtk::TreeModel::Row row = *iter;
            number = row[colums.id];
            response(Gtk::RESPONSE_OK);
        }
        else if(treemodel->children().size() > 0)
        {
            Gtk::TreeModel::Row row = treemodel->children()[0];
            number = row[colums.id];
            response(Gtk::RESPONSE_OK);
        }

    }







}
