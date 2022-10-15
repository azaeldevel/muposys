
#include <gtkmm/application.h>

#include "desk.hh"

namespace mps
{

Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade), devel(false)
{	
	init();
		
	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
	show();
}
Main::Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool d) : Gtk::Window(cobject), builder(refGlade),devel(d)
{	
	init();
			
	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
	show();
}
void Main::init()
{	
	if(is_visible()) throw Exception(Exception::VISIBLE_MAIN,__FILE__,__LINE__);
	
	add_events(Gdk::KEY_PRESS_MASK);		
	
	hb_muposys = 0;
	builder->get_widget("hb_muposys", hb_muposys);	
	
	lbUser = 0;
	builder->get_widget("lbUser", lbUser);
	
	boxSlices = 0;
	builder->get_widget("boxSlices", boxSlices);	
	
	nbMain = 0;
	builder->get_widget("nbMain", nbMain);
	
#ifdef ENABLE_DEVEL
	add_activity(sales);
	show_all_children();
#endif
}
Main::~Main()
{
}

void Main::check_session()
{
	builder->get_widget_derived("Login", login);
	login->set_transient_for((Gtk::Window&)*this);	
	if(devel) login->set_session("root","123456");
	int res = Gtk::RESPONSE_NONE;
	do
	{
		if (login)
		{
			res = login->run();
		}	
		switch(res)
		{
		case Gtk::RESPONSE_OK:
			break;	
		case Gtk::RESPONSE_CANCEL:
			login->close();
			return;	
		case Gtk::RESPONSE_NONE:
			break;			
		}
	}
	while(not login->get_credential().valid);
	
	
	if(login->get_credential().valid)
	{	
		//std::cout << "User valid " << login->get_credential().user << "..\n";
		credential = login->get_credential();
		lbUser->set_text(credential.user);
	}
	login->close();
}

/*void Main::set_title(const char* )
{
	
}
void Main::set_subtitle(const char* )
{
	
}*/

void Main::add_activity(Gtk::Widget& w)
{
	nbMain->append_page(w);	
}






Login::Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Dialog(cobject), builder(refGlade), retcode(Gtk::RESPONSE_NONE)
{
	lbmsg = 0;
	builder->get_widget("msg", lbmsg);
	
	btOK = 0;
	builder->get_widget("btOK", btOK);
	btOK->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_ok_clicked));
	
	btCancel = 0;
	builder->get_widget("btCancel", btCancel);
	btCancel->signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_cancel_clicked));
		
	inPwd = 0;
	builder->get_widget("inPwd", inPwd);
	
	inUser = 0;
	builder->get_widget("inUser", inUser);
	//inUser->signal_key_press_event().connect(sigc::mem_fun(*this,&Login::on_in_user_enter));
	
	//set_default_size(250,150);
	set_modal(true);
}

Login::~Login()
{
}

int Login::run()
{
	show();
	Gtk::Dialog::run();
	return retcode;
}

void Login::on_bt_cancel_clicked()
{
	retcode = Gtk::RESPONSE_CANCEL;
	close();
}

void Login::on_bt_ok_clicked()
{
	retcode = Gtk::RESPONSE_OK;
	check_user();
	close();	
}

bool Login::on_in_user_enter(GdkEventKey* e)
{
	//if(e->keyval == GDK_KEY_KP_Enter)
	{
		std::cout << "Enter detected\n";
		inPwd->set_text("");
		inPwd->grab_focus();
	}
	
	return false;
}

void Login::check_user()
{
	Connector connDB;
	bool flag = false;
	int res = 0;
	try
	{
		flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		Gtk::MessageDialog dlg(*this,"Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		res = dlg.run();
		return;		
	}
	
	credential.valid = true;
	
	std::string strwhere = "name = ";
	strwhere += "'" + inUser->get_text() + "' and pwdtxt = '" + inPwd->get_text() + "' and status = 'A'";
	std::vector<muposysdb::Users*>* userlst = muposysdb::Users::select(connDB,strwhere);
	
	//std::cout << "SQL str : " << strwhere << "\n";
	
	if(userlst == NULL) 
	{
		credential.valid = false;
		std::cout << "No hay resultado de la consulta\n";
	}
	if(userlst->size() == 0) 
	{		
		credential.valid = false;
		std::cout << "Hay 0 resultados de la consulta\n";
	}
	if(userlst->size() > 1) 
	{
		credential.valid = false;
		std::cout << "Hay " <<  userlst->size() << " resultados de la consulta\n";
	}	
	
	if(not credential.valid)//si no es valido el usario liberar memorio y salir
	{
		lbmsg->set_text("Usuario/Contraseña incorrectos.");
		for(auto u : *userlst)
		{
			if(u->getPerson().downName1(connDB))
			{
				if(u->getPerson().downName3(connDB))
				{
					credential.name = u->getPerson().getName1() + " " + u->getPerson().getName3();
				}
			}
			else
			{
				credential.name = u->getPerson().getName1();
			}
			delete u;
		}
		delete userlst;		
		return;
	}
	//std::cout << "Usuario aceptado\n";
	credential.user = inUser->get_text();
}
const Login::Credential& Login::get_credential() const
{
	return credential;
}
void Login::set_session(const char* u,const char* p)
{	
	inUser->set_text(u);
	inPwd->set_text(p);	
}






Restaurant::Restaurant(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Main(cobject,refGlade)
{
}
Restaurant::Restaurant(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool d) : Main(cobject,refGlade,d)
{
}
Restaurant::~Restaurant()
{
}





TableSaling::TableSaling() : Gtk::Box(Gtk::ORIENTATION_VERTICAL)
{
	init();	
}
void TableSaling::init()
{
	set_valign(Gtk::ALIGN_CENTER);
	pack_start(table);
	
	tree_model = Gtk::ListStore::create(columns);
	tree_model->signal_row_changed().connect(sigc::mem_fun(*this, &TableSaling::row_changed));
	table.set_model(tree_model);
	
	table.append_column_editable("Cant.", columns.quantity);
	Gtk::CellRendererSpin* cell_quantity = static_cast<Gtk::CellRendererSpin*>(table.get_column_cell_renderer(table.get_n_columns() - 1));
	Gtk::TreeViewColumn* col_quantity = table.get_column(table.get_n_columns() - 1);
	cell_quantity->property_editable() = true;
	//col_quantity->set_cell_data_func(*cell_quantity,sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data_quantity));
	//cell_quantity->signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started_quantity));
	//cell_quantity->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_quantity));	
	table.append_column("Present.", columns.presentation);
	table.append_column_editable("Number", columns.number);
	Gtk::CellRendererText* cell_number = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(table.get_n_columns() - 1));
	Gtk::TreeViewColumn* col_number = table.get_column(table.get_n_columns() - 1);
	//col_number->set_cell_data_func(*cell_number,sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data_number));
	cell_number->property_editable() = true;
	cell_number->signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started_number));
	cell_number->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_number));
	
	table.append_column("Artículo", columns.name);
	table.append_column_numeric_editable("Costo", columns.cost,"%.2f");
		
	newrow();	
	
	pack_start(boxTotal);	
	boxTotal.set_halign(Gtk::ALIGN_START);
	boxTotal.pack_start(lbTotal);
	lbTotal.set_text("Total : $");
	boxTotal.pack_start(lbTotalAmount);
	lbTotalAmount.set_text("00000000.00");
	
	/*
	column_validated.set_title("editando..)");
	column_validated.pack_start(cell_render);
	append_column(column_validated);
	column_validated.set_cell_data_func(cell_render, sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data));
	cell_render.property_editable() = true;
	cell_render.signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started) );
	cell_render.signal_edited().connect( sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited) );
	*/
		
	
	//loading data
	/*
	Gtk::TreeModel::Row row = *(tree_model->append());
	row[columns.id] = 1;
	row[columns.item] = 1;
	row[columns.amount] = 1;
	row[columns.presentation] = "Pz";
	row[columns.number] = "ppp";
	row[columns.name] = "Chica - Peperoni";
	row[columns.cost] = 115;
	
	row = *(tree_model->append());
	row[columns.id] = 2;
	row[columns.item] = 1;
	row[columns.amount] = 1;
	row[columns.presentation] = "Pz";
	row[columns.number] = "gmx";
	row[columns.name] = "Grande - Mexiana";
	row[columns.cost] = 235;
	*/
}
TableSaling::~TableSaling()
{
}
TableSaling::ModelColumns::ModelColumns()
{
	add(id);
	add(item);
	add(quantity);
	add(presentation);
	add(number);
	add(name);
	add(cost);
}

void TableSaling::row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
{
	//std::cout << "Size : " << tree_model->children().size() << "\n";		
	const Gtk::TreeModel::iterator last = --(tree_model->children().end());
	if(last == iter) newrow();
	
	lbTotalAmount.set_text(std::to_string(total()));
}

/*
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
*/

void TableSaling::treeviewcolumn_validated_on_cell_data_number( Gtk::CellRenderer* renderer , const Gtk::TreeModel::iterator& iter)
{
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring model_value = row[columns.number];
		
		static_cast<Gtk::CellRendererText*>(renderer)->property_text() = model_value;
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
void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);
	
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Falló la conexión a la Base de datos",__FILE__,__LINE__);
		
	std::string where = "number = '" + new_text + "'";
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = muposysdb::Catalog_Items::select(connector,where);
	//std::cout << "where : " << where << "\n";
	
	if(not lstCatItems) return;
	
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downName(connector);
		lstCatItems->front()->downValue(connector);
		lstCatItems->front()->downPresentation(connector);
		
			Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
			if(iter)
			{
				Gtk::TreeModel::Row row = *iter;
				//Put the new value in the model:
				row[columns.number] = new_text;
				row[columns.name] = lstCatItems->front()->getName();
				row[columns.presentation] = lstCatItems->front()->getPresentation();
				row[columns.cost] = row[columns.quantity] * lstCatItems->front()->getValue();
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
	Gtk::CellRendererSpin* cell = dynamic_cast<Gtk::CellRendererSpin*>(cell_editable);
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
		cell->property_text() = "#";
		return;
	}
	catch(const std::out_of_range& e)
	{
		row[columns.quantity_valid] = false;
		cell->property_text() = "#";
		return;		
	}
	
	cell->property_text() = entry->get_text();
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
	
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Falló la conexión a la Base de datos",__FILE__,__LINE__);
		
	std::string where = "number = '" + new_text + "'";
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = muposysdb::Catalog_Items::select(connector,where);
	//std::cout << "where : " << where << "\n";
	
	if(not lstCatItems) return;
	
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downName(connector);
		lstCatItems->front()->downValue(connector);
		lstCatItems->front()->downPresentation(connector);
		
			Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
			if(iter)
			{
				Gtk::TreeModel::Row row = *iter;
				//Put the new value in the model:
				row[columns.number] = new_text;
				row[columns.name] = lstCatItems->front()->getName();
				row[columns.presentation] = lstCatItems->front()->getPresentation();
				row[columns.cost] = row[columns.quantity] * lstCatItems->front()->getValue();
			}
	}
	for(muposysdb::Catalog_Items* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;
}


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
		tt += row[columns.cost];
	}
	return tt;
}











}

