
#include "Catalog.hh"


namespace muposys
{
	
CatalogSupplier::CatalogSupplier(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	set_size_request(400,200);

	localconection = true;//conexion local
	try
	{
		connector = new octetos::db::maria::Connector();
		connector->connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{		
		std::cerr << e.what() << "\n";
		return;
	}


	builder->get_widget("search", search);
	search->signal_key_release_event().connect(sigc::mem_fun(*this, &CatalogSupplier::on_search_KeyPress),false);
	
	builder->get_widget("btCreateItem", btCreateItem);
	btCreateItem->signal_clicked().connect(sigc::mem_fun(*this,&CatalogSupplier::on_btCatalogData_clicked));

	builder->get_widget("treeData", treeData);
	//http://transit.iut2.upmf-grenoble.fr/doc/gtkmm-3.0/tutorial/html/sec-treeview-examples.html
	//treeview
	m_refTreeModel = Gtk::ListStore::create(m_Columns);
  	treeData->set_model(m_refTreeModel);
	treeData->append_column("Numero", m_Columns.number);
	treeData->append_column("Descripcion", m_Columns.brief);
}
CatalogSupplier::~CatalogSupplier()
{
 	if(localconection) connector->close();
}

bool CatalogSupplier::on_search_KeyPress(GdkEventKey* event)
{
	//std::cout << search->get_text() << "\n";
	m_refTreeModel->clear();
	std::string where = "number LIKE '";
	where += search->get_text() + "%' OR brief LIKE '%" + search->get_text() + "%'";
	std::vector<muposysdb::CatalogSupplier*>* lst = CatalogSupplierData::select(*connector,where);
	if(lst->size() == 0) return false;
	Gtk::TreeModel::Row row;
	for(muposysdb::CatalogSupplier* c : *lst)
	{
		row = *(m_refTreeModel->append());
		row[m_Columns.id] = c->getItemValue();
		c->downNumber(*connector);
	  	row[m_Columns.number] = c->getNumber();
		c->downBrief(*connector);
		row[m_Columns.brief] = c->getBrief();
	}
	
	delete lst;
	return false;
}
void CatalogSupplier::on_btCatalogData_clicked()
{
	CatalogSupplierData* wndCatalogData = 0;
	builder->get_widget_derived("wndCatalogData", wndCatalogData);
	wndCatalogData->show();
}
CatalogSupplier::ModelColumns::ModelColumns()
{
	add(number);
	add(brief);
}






CatalogSupplierData::CatalogSupplierData(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	connector = NULL;
	
	builder->get_widget("inNumber", inNumber);
	builder->get_widget("opService", opService);
	builder->get_widget("opItem", opItem);
	builder->get_widget("inBrief", inBrief);
	builder->get_widget("btAcceptCatalogData", btAccept);
    builder->get_widget("btCancelCatalogData", btCancel);

	
	btAccept->signal_clicked().connect(sigc::mem_fun(*this, &CatalogSupplierData::on_accept_button_clicked));
    btCancel->signal_clicked().connect(sigc::mem_fun(*this, &CatalogSupplierData::on_cancel_button_clicked));
	
}
void CatalogSupplierData::on_accept_button_clicked()
{
	//std::cout << "Step 1.\n";
	//valid inputs
	if(inNumber->get_text_length() == 0)
	{
		std::cout << "Capture el numero de parte.\n";
		return;
	}
	if(inBrief->get_text_length() == 0)
	{
		std::cout << "Capture la descripcion.\n";
		return;
	}

	//std::cout << "Step 2.\n";

	
	bool localconection = false;
	if(!connector)//si no hay conecion crearla
	{
		localconection = true;//conexion local
		try
		{
			//std::cout << "Step 2.1.\n";
			connector = new octetos::db::maria::Connector();
			connector->connect(muposysdb::datconex);
			//std::cout << "Step 2.2.\n";
		}
		catch(const std::exception& e)
		{		
			std::cerr << e.what() << "\n";
			return;
		}
		//std::cout << "Step 2.3.\n";
	}

	//std::cout << "Step 3.\n";
	

	std::string type;
	if(opService->get_active())
	{
		type = "service";
	}
	else if(opItem->get_active())
	{
		type = "item";
	}

	//std::cout << "Step 4.\n";
	
	bool fljob = insert(*connector,inNumber->get_text(),type,inBrief->get_text());

	//commit si es una conexion local
	if(fljob and localconection) connector->commit(); 
	
	//std::cout << "Step 5.\n";
	
	if(localconection)//si es una conexion local
	{
		delete connector;
		connector = NULL;
	}
	if(fljob) close();
}

void CatalogSupplierData::on_cancel_button_clicked()
{
    
}

}