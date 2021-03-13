

#ifndef MUPOSYS_BUYS_HH
#define MUPOSYS_BUYS_HH

#include <gtkmm.h>


#include "muposysdb.hpp"


namespace muposys
{

class Buys : public Gtk::Window
{
public:
	Buys(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Buys();
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::ToolButton* btCreateItem;
	Gtk::SearchEntry* search;

	void on_btBuysData_clicked();
	bool on_search_KeyPress(GdkEventKey* event);
private:

	class ModelColumns : public Gtk::TreeModel::ColumnRecord
  	{
  	public:
		ModelColumns();

		Gtk::TreeModelColumn<int> id;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<Glib::ustring> nameShort;
  	};

	ModelColumns m_Columns;
 	Gtk::TreeView* treeData;
  	Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
	
	octetos::db::maria::Connector* connector;
	bool localconection;
};

}

#endif