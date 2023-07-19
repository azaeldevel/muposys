
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 *
 * muposys is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * octetos-cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "desk.hh"

namespace mps
{


TableSaling::TableSaling() : connDB_flag(false),notebook(NULL),notebook_page_index(0),crud(Crud::create),order(-1)
{
    //std::cout << "mps::TableSaling::TableSaling()\n";
	init();
}
TableSaling::TableSaling(long o) : connDB_flag(false),notebook(NULL),notebook_page_index(0),crud(Crud::read),order(o)
{
    //std::cout << "mps::TableSaling::TableSaling(long)\n";
	init();
}
TableSaling::TableSaling(long o,mps::Crud c) : connDB_flag(false),notebook(NULL),notebook_page_index(0),crud(c),order(o)
{
    //std::cout << "mps::TableSaling::TableSaling(long)\n";
	init();
}
void TableSaling::init()
{
	/*try
	{
		connDB_flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();
		return;
	}*/

	set_valign(Gtk::ALIGN_CENTER);
	table.add_events(Gdk::KEY_PRESS_MASK);
	//table.signal_key_press_event().connect(sigc::mem_fun(*this, &TableSaling::on_key_press_event));
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
		//col_quantity->set_cell_data_func(*cell_quantity,sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data_quantity));
		//cell_quantity->signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started_quantity));
		//cell_quantity->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_quantity));

		table.append_column("Present.", columns.presentation);

		if(crud == Crud::create)table.append_column_editable("Number", columns.number);
		else table.append_column("Number", columns.number);
		//Gtk::CellRendererText* cell_number = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(table.get_n_columns() - 1));
		//Gtk::TreeViewColumn* col_number = table.get_column(table.get_n_columns() - 1);
		//col_number->set_cell_data_func(*cell_number,sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data_number));
		//cell_number->property_editable() = true;
		//cell_number->signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started_number));
		//cell_number->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_number));

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
#ifdef MUPOSYS_DESK_ENABLE_TDD
		btSave.signal_clicked().connect( sigc::mem_fun(*this,&TableSaling::on_save_clicked));
#endif
		btSave.set_image_from_icon_name("document-save");
		boxFloor.pack_start(btSave,Gtk::PACK_SHRINK);
	}

	saved = true;

	if(crud == Crud::create) newrow();
}
TableSaling::~TableSaling()
{
	//if(connDB_flag) connDB.close();
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
    //if(int(row[columns.quantity]) > 0) row[columns.amount] = row[columns.quantity] * row[columns.cost_unit];

	//std::cout << "Size : " << tree_model->children().size() << "\n";
	const Gtk::TreeModel::iterator& last = --(tree_model->children().end());

	if(last == iter and crud == Crud::create) newrow();

	lbTotalAmount.set_text(std::to_string(total()));
	if(notebook) mark_unsave();

	saved = false;
}
void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);

	/*std::string where = "number = '" + new_text + "'";
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connDB,where);
	//std::cout << "where : " << where << "\n";

	if(not lstCatItems) return;

	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downBrief(connDB);
		lstCatItems->front()->downValue(connDB);
		lstCatItems->front()->downPresentation(connDB);

        Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
        if(iter)
        {
            Gtk::TreeModel::Row row = *iter;
            row[columns.item] = lstCatItems->front()->getID();
            row[columns.number] = new_text;
            row[columns.name] = lstCatItems->front()->getBrief();
            row[columns.presentation] = lstCatItems->front()->getPresentation();
            row[columns.cost_unit] = lstCatItems->front()->getValue();
            row[columns.amount] = row[columns.quantity] * row[columns.cost_unit];
        }
	}
	for(muposysdb::CatalogItem* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;*/
}

void TableSaling::newrow()
{
	//Gtk::TreeModel::Row row = *tree_model->append();
	/*
	row[columns.quantity] = 0;
	row[columns.cost_unit] = 0.0;
	row[columns.amount] = 0.0;
	*/
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


bool TableSaling::on_quantity_key_press_event(GdkEventKey* key_event)
{
	//std::cout << "key quantity : " << (char) key_event->keyval << "\n";
	return false;
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
void TableSaling::download(long order)
{
    std::string whereOrder;
    whereOrder = "operation = ";
    whereOrder += std::to_string(order);
    /*std::vector<muposysdb::Sale*>* lstSales = muposysdb::Sale::select(connDB,whereOrder,0,'A');
    if(lstSales)
    {
        for(auto s : *lstSales)
        {
            delete s;
        }
        delete lstSales;
    }*/

}



















#ifdef MUPOSYS_DESK_ENABLE_TDD
void TableSaling::on_save_clicked()
{
	save();
}
void TableSaling::save()
{
	//std::cout << "saving..\n";
	Gtk::TreeModel::Row row;
	//muposysdb::Ente *ente_service,*ente_operation;
	muposysdb::Stock stock(9);
	muposysdb::Stocking* stocking;
	muposysdb::CatalogItem* cat_item;
	muposysdb::Operation* operation;
	muposysdb::Progress* operationProgress;
	const Gtk::TreeModel::iterator& last = (tree_model->children().end());
	int quantity,item;
	/*ente_service = new muposysdb::Ente;
	if(not ente_service->insert(connDB))
	{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura del ID Stoking.");
			dlg.run();
			return;
	}*/
	operation = new muposysdb::Operation;
	if(not operation->insert(connDB))
	{
			Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking Production.");
			dlg.run();
			return;
	}
	/*if(not operation->upStep(connDB,0))
	{
			Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking Production para step.");
			dlg.run();
			return;
	}*/

	/*ente_operation = new muposysdb::Ente;
	if(not ente_operation->insert(connDB))
	{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura del ID Stoking.");
			dlg.run();
			return;
	}*/
	for(const Gtk::TreeModel::const_iterator& it : tree_model->children())
	{
		if(last == it) break;
		row = *it;

		quantity = row[columns.quantity];
		if(quantity == 0) break;

		item = row[columns.item];

		cat_item = new muposysdb::CatalogItem(item);

		cat_item->downType(connDB);
		if(cat_item->getType() == 1)
		{
			for(unsigned int i = 0; i < quantity; i++ )
			{
				stocking = new muposysdb::Stocking;
				if(not stocking->insert(connDB,stock,*cat_item,-1))
				{
					Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking.");
					dlg.run();
					return;
				}
				//muposysdb::User user(2);
				operationProgress = new muposysdb::Progress;
				if(not operationProgress->insert(connDB,*stocking,*operation,0))
				{
					Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking Production.");
					dlg.run();
					return;
				}
				delete operationProgress;
				delete stocking;
			}
		}
		else
		{
			stocking = new muposysdb::Stocking;
			if(not stocking->insert(connDB,stock,*cat_item,-quantity))
			{
				Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
				dlg.set_secondary_text("Durante la escritura de Stoking.");
				dlg.run();
				return;
			}
			delete stocking;
		}

		delete cat_item;
	}

	//delete ente_service;
	//delete ente_operation;

	muposysdb::Sale* sale;
	for(const Gtk::TreeModel::const_iterator& it : tree_model->children())
	{
		if(last == it) break;
		row = *it;

		quantity = row[columns.quantity];
		if(quantity == 0) break;

		item = row[columns.item];
		cat_item = new muposysdb::CatalogItem(item);

		sale = new muposysdb::Sale;
		if(not sale->insert(connDB,*operation,stock,*cat_item,quantity))
		{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking.");
			dlg.run();
			return;
		}

		delete cat_item;
	}

	delete operation;

	connDB.commit();
	clear();

	Gtk::MessageDialog dlg("Operacion completada.",true,Gtk::MESSAGE_INFO);
	dlg.set_secondary_text("La Venta se realizo satisfactoriamente.");
	dlg.run();
}
#endif










/*

bool TableSaling::on_key_press_event(GdkEventKey* key_event)
{
	std::cout << "key tree " << (char) key_event->keyval << "\n";

	return false;
}
void TableSaling::treeviewcolumn_validated_on_cell_data( Gtk::CellRenderer* renderer , const Gtk::TreeModel::iterator& iter)
{
	//Get the value from the model and show it appropriately in the view:
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring model_value = row[columns.number_validated];

		//This is just an example.
		//In this case, it would be easier to use append_column_editable() or
		//append_column_numeric_editable()
		char buffer[32];
		sprintf(buffer, "%d", model_value);

		Glib::ustring view_text = buffer;
		cell_render.property_text() = "---" + view_text + "---";
	}
}
void TableSaling::cellrenderer_validated_on_editing_started( Gtk::CellEditable* cell_editable, const Glib::ustring&)
{

	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Fallo la conexión a la Base de datos",__FILE__,__LINE__);

	if(validate_retry)
	{
		auto celleditable_validated = cell_editable;

		auto pEntry = dynamic_cast<Gtk::Entry*>(celleditable_validated);
		if(pEntry)
		{
			pEntry->set_text(invalid_text_for_retry);
			validate_retry = false;
			invalid_text_for_retry.clear();
		}
	}
}
void TableSaling::cellrenderer_validated_on_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);

	if(new_text.size() > 3)
	{
		std::cout << "Error : " << new_text << "\n";

		invalid_text_for_retry = new_text;
		validate_retry = true;

		set_cursor(path, column_validated,cell_render, true);
	}
	else
	{
		Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
		if(iter)
		{
			Gtk::TreeModel::Row row = *iter;
			row[columns.number_validated] = new_text;
		}
	}
}
void TableSaling::treeviewcolumn_validated_on_cell_data_number( Gtk::CellRenderer* renderer , const Gtk::TreeModel::iterator& iter)
{
	if(not connDB_flag) return;

	Gtk::TreeModel::Row row = *iter;
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = NULL;

	auto cell = dynamic_cast<Gtk::CellRendererText*>(renderer);
	if(cell)
	{
		std::string where = "number = '" + cell->property_text() + "'";
		//std::cout << "where : " << where << "\n";
		try
		{
			lstCatItems = muposysdb::Catalog_Items::select(connDB,where);
		}
		catch(const std::exception& e)
		{
			Gtk::MessageDialog dlg("Error detectado durante consulta a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text(e.what());
			dlg.run();
			return;
		}
	}

	bool validated  = false;
	if(not lstCatItems) return;

	if(lstCatItems->size() == 1)
	{
		validated = true;
		try
		{
			if(lstCatItems->front()->downName(connDB))
			{
				std::cout << "name : " << lstCatItems->front()->getName() << "\n";
				row[columns.item] = lstCatItems->front()->getID().getID();
				row[columns.name] = "tests..";
				//row[columns.name] = lstCatItems->front()->getName();
			}
		}
		catch(const std::exception& e)
		{
			Gtk::MessageDialog dlg("Error detectado durante consulta a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text(e.what());
			dlg.run();
			return;
		}
	}
	for(muposysdb::Catalog_Items* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;

	if(not validated)
	{
		//row[columns.name] = "";
	}

}
void TableSaling::cellrenderer_validated_on_editing_started_number( Gtk::CellEditable* cell_editable, const Glib::ustring& path)
{
	Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
	Gtk::TreeModel::Row row = *iter;

	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Falló la conexión a la Base de datos",__FILE__,__LINE__);

	std::vector<muposysdb::Catalog_Items*>* lstCatItems = NULL;

	auto pEntry = dynamic_cast<Gtk::Entry*>(cell_editable);
	if(pEntry)
	{
		std::string where = "number = '" + pEntry->get_text() + "'";
		lstCatItems = muposysdb::Catalog_Items::select(connector,where);
		//std::cout << "where : " << where << "\n";
	}

	row[columns.number_validated]  = false;
	if(not lstCatItems) return;

	if(lstCatItems->size() == 1)
	{
		if(lstCatItems->front()->downName(connector))
		{
			row[columns.name] = lstCatItems->front()->getName();
			row[columns.number_validated] = true;
		}
	}
	for(muposysdb::Catalog_Items* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;
}
void TableSaling::treeviewcolumn_validated_on_cell_data_quantity( Gtk::CellRenderer* cell_editable , const Gtk::TreeModel::iterator& iter)
{
	Gtk::Entry* entry = dynamic_cast<Gtk::Entry*>(cell_editable);
	Gtk::CellRendererText* cell = dynamic_cast<Gtk::CellRendererText*>(cell_editable);
	Gtk::TreeModel::Row row = *iter;
	row[columns.quantity_valid] = false;

	unsigned long number;
	try
	{
		number = std::stoul((std::string)entry->get_text());
	}
	catch(const std::invalid_argument& e)
	{
		row[columns.quantity_valid] = false;
		cell->property_text() = "";
		return;
	}
	catch(const std::out_of_range& e)
	{
		row[columns.quantity_valid] = false;
		cell->property_text() = "";
		return;
	}

	row[columns.quantity] = number;
	row[columns.amount] = row[columns.quantity] * row[columns.cost_unit];

}
void TableSaling::cellrenderer_validated_on_editing_started_quantity( Gtk::CellEditable* cell_editable, const Glib::ustring& path)
{
	Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
	Gtk::Entry* entry = dynamic_cast<Gtk::Entry*>(cell_editable);
	Gtk::TreeModel::Row row = *iter;
	row[columns.quantity_valid] = false;

	unsigned long number;
	try
	{
		number = std::stoul(entry->get_text());
	}
	catch(const std::invalid_argument& e)
	{
		row[columns.quantity_valid] = false;
		return;
	}
	catch(const std::out_of_range& e)
	{
		row[columns.quantity_valid] = false;
		return;
	}

	row[columns.quantity_valid] = true;
}
void TableSaling::cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);

	Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		row[columns.amount] = row[columns.quantity] * row[columns.cost_unit];
		std::cout << "amount : " << row[columns.amount] << "\n";
	}
}
*/





}

