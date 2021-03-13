
#ifndef MUPOSYS_CATALOG_HH
#define MUPOSYS_CATALOG_HH

#include <gtkmm.h>


#include "muposysdb.hpp"


namespace muposys
{

class CatalogData : public Gtk::Window, public muposysdb::Catalog
{
public:
	CatalogData(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Entry* inNumber;
	Gtk::RadioButton *opService,*opItem;
	Gtk::Entry* inBrief;
	Gtk::Button* btAccept;
	Gtk::Button* btCancel;

    void on_accept_button_clicked();
    void on_cancel_button_clicked();
private:
	octetos::db::maria::Connector* connector;

};


class Catalog : public Gtk::Window
{
public:
	Catalog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Catalog();
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::ToolButton* btCreateItem;
	Gtk::SearchEntry* search;

	void on_btCatalogData_clicked();
	bool on_search_KeyPress(GdkEventKey* event);
private:

	class ModelColumns : public Gtk::TreeModel::ColumnRecord
  	{
  	public:
		ModelColumns();

		Gtk::TreeModelColumn<int> id;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<Glib::ustring> brief;
  	};

	ModelColumns m_Columns;
 	Gtk::TreeView* treeData;
  	Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
	
	octetos::db::maria::Connector* connector;
	bool localconection;
};



}

#endif