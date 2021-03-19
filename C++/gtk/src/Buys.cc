

#include "Buys.hh"
#include "Catalog.hh"



namespace muposys
{


Movements::Movements(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	connector = NULL;
	supplier = NULL;
	item = NULL;
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
	
	set_size_request(600,300);

	builder->get_widget("inSupplierMovements", inSupplier);
	inSupplier->signal_key_release_event().connect(sigc::mem_fun(*this, &Movements::on_searchSupplier_KeyPress),false);
	builder->get_widget("lbSupplierMovements", lbSupplier);
	builder->get_widget("inItemNumberMovements", inItemNumber);
	inItemNumber->signal_key_release_event().connect(sigc::mem_fun(*this, &Movements::on_searchNumber_KeyPress),false);
	
}	
Movements::~Movements()
{
	if(supplier) delete supplier;
}
bool Movements::on_searchSupplier_KeyPress(GdkEventKey* event)
{
	std::string where = "number LIKE '";
	where += inSupplier->get_text() + "%' OR nameShort LIKE '%" + inSupplier->get_text() + "%'";
	std::vector<muposysdb::Supplier*>* lst = SupplierData::select(*connector,where,1);
	if(lst->size() > 0)
	{
		muposysdb::Supplier* s = lst->at(0);
		s->downNumber(*connector);
		s->downNameShort(*connector);
		//std::cout << "input " << inSupplier->get_text() << "\n";
		if(s->getNumber() == std::stoi(inSupplier->get_text()))
		{
			std::string str = "\t" + std::to_string(s->getNumber()) + " - " + s->getNameShort();
			//std::cout << " label " << str << "\n";
			supplier = new muposysdb::Supplier(*s);
			lbSupplier->set_text(str);
			return true;
		}
		else
		{
			cleanSupplier();
		}
	}
	else
	{
		cleanSupplier();
	}
	
	delete lst;
	return false;
}
bool Movements::on_searchNumber_KeyPress(GdkEventKey* event)
{
	std::string where = "number LIKE '";
	where += inItemNumber->get_text() + "%' OR brief LIKE '%" + inItemNumber->get_text() + "%'";
	std::vector<muposysdb::CatalogSupplier*>* lst = CatalogSupplierData::select(*connector,where,1);
	if(lst->size() > 0)
	{
		muposysdb::CatalogSupplier* i = lst->at(0);
		i->downNumber(*connector);
		i->downBrief(*connector);
		std::cout << "input " << inSupplier->get_text() << "\n";
		if(strcmp(i->getNumber().c_str(),inItemNumber->get_text().c_str()) == 0)
		{
			//std::cout << " item : " << i->getBrief() << "\n";
			auto cobj = gobj();
			item = new muposysdb::CatalogSupplier(*i);
			return true;
		}
		else
		{
			cleanCatalogSupplier();
		}
	}
	else
	{
		cleanCatalogSupplier();
	}
	
	delete lst;
	return false;
}

void Movements::cleanSupplier()
{
	lbSupplier->set_text("\t###");
	if(supplier) 
	{
		delete supplier;
		supplier = NULL;
	}
}
void Movements::cleanCatalogSupplier()
{
	if(item) 
	{
		delete item;
		item = NULL;
	}
}




Buys::Buys(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
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
	search->signal_key_release_event().connect(sigc::mem_fun(*this, &Buys::on_search_KeyPress),false);
	
	builder->get_widget("btNewBuy", btNew);
	btNew->signal_clicked().connect(sigc::mem_fun(*this,&Buys::on_btBuysCreateMov_clicked));

	builder->get_widget("treeData", treeData);
	//http://transit.iut2.upmf-grenoble.fr/doc/gtkmm-3.0/tutorial/html/sec-treeview-examples.html
	//treeview
	m_refTreeModel = Gtk::ListStore::create(m_Columns);
  	treeData->set_model(m_refTreeModel);
	treeData->append_column("Numero", m_Columns.number);
}
Buys::~Buys()
{
 	if(localconection) connector->close();
}

bool Buys::on_search_KeyPress(GdkEventKey* event)
{

	
	return false;
}
void Buys::on_btBuysCreateMov_clicked()
{
	Movements* wndMovements = 0;
	builder->get_widget_derived("wndMovements", wndMovements);
	wndMovements->show();
}
Buys::ModelColumns::ModelColumns()
{
	
}




SupplierData::SupplierData(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), builder(refGlade)
{
	connector = NULL;
	
	builder->get_widget("inNumber", inNumber);
	builder->get_widget("inNameShort", inNameShort);
	builder->get_widget("btAcceptCatalogData", btAccept);
    builder->get_widget("btCancelCatalogData", btCancel);

	
	btAccept->signal_clicked().connect(sigc::mem_fun(*this, &SupplierData::on_accept_button_clicked));
    btCancel->signal_clicked().connect(sigc::mem_fun(*this, &SupplierData::on_cancel_button_clicked));
	
}
void SupplierData::on_accept_button_clicked()
{
	//std::cout << "Step 1.\n";
	//valid inputs
	if(inNumber->get_text_length() == 0)
	{
		std::cout << "Capture el numero de parte.\n";
		return;
	}
	if(inNameShort->get_text_length() == 0)
	{
		std::cout << "Capture la descripcion.\n";
		return;
	}
		
	

	
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
		
	bool fljob = insert(*connector,std::stoi(inNumber->get_text()),inNameShort->get_text());

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

void SupplierData::on_cancel_button_clicked()
{
    close();
}

}



