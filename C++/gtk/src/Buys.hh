

#ifndef MUPOSYS_BUYS_HH
#define MUPOSYS_BUYS_HH

#include <gtkmm.h>


#include "muposysdb.hpp"
#include "Catalog.hh"

namespace muposys
{

class SupplierData : public Gtk::Window, public muposysdb::Supplier
{
public:
	SupplierData(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Entry* inNumber;
	Gtk::Entry* inNameShort;
	Gtk::Button* btAccept;
	Gtk::Button* btCancel;

    void on_accept_button_clicked();
    void on_cancel_button_clicked();
private:
	octetos::db::maria::Connector* connector;

};

class Movements : public Gtk::Window
{
public:
	Movements(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Movements();
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Entry* inSupplier;
	Gtk::Label* lbSupplier;
	Gtk::Entry* inItemNumber;
	muposysdb::CatalogSupplier* item;

	bool on_searchSupplier_KeyPress(GdkEventKey* event);
	bool on_searchNumber_KeyPress(GdkEventKey* event);
private:
	octetos::db::maria::Connector* connector;
	muposysdb::Supplier* supplier;
	bool localconection;

	//funtion
	void cleanSupplier();
	void cleanCatalogSupplier();
};

class Buys : public Gtk::Window
{
public:
	Buys(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Buys();
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::ToolButton* btNew;
	Gtk::SearchEntry* search;

	void on_btBuysCreateMov_clicked();
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