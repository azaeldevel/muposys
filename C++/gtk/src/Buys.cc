

#include "Buys.hh"


namespace muposys
{
	
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
	
	builder->get_widget("btCreateItem", btCreateItem);
	btCreateItem->signal_clicked().connect(sigc::mem_fun(*this,&Buys::on_btBuysData_clicked));

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
	
}
void Buys::on_btBuysData_clicked()
{
	
}
Buys::ModelColumns::ModelColumns()
{
	
}

}



