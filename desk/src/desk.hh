
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/apidb.hh>
#include <gtkmm.h>
#include <muposys/Exception.hh>

namespace mps
{

	
class TableSaling : public Gtk::VBox
{	
public:
	TableSaling();	
	void init();
	virtual ~TableSaling();
	
protected:
	
	Connector connDB;
	bool connDB_flag;
	
	void row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
	
	void treeviewcolumn_validated_on_cell_data_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_number(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	void treeviewcolumn_validated_on_cell_data_quantity(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_quantity(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	bool on_key_press_event(GdkEventKey* key_event);
	bool on_quantity_key_press_event(GdkEventKey* key_event);
	
	void on_save_clicked();
	
	float total()const;
	
	void newrow();
	
	void clear();
	
private:
	
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();
		//Gtk::TreeModelColumn<unsigned int> id;		
		Gtk::TreeModelColumn<int> item;
		Gtk::TreeModelColumn<int> quantity;
		//Gtk::TreeModelColumn<bool> quantity_valid;
		Gtk::TreeModelColumn<Glib::ustring> presentation;
		Gtk::TreeModelColumn<Glib::ustring> number;
		//Gtk::TreeModelColumn<bool> number_validated;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<float> cost_unit;
		Gtk::TreeModelColumn<float> amount;
		//Gtk::TreeModelColumn<bool> amount_valid;
	};
	
	ModelColumns columns;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	Gtk::TreeView table;
	Gtk::Button btSave;
	Gtk::Label lbTotal,lbTotalAmount;
	Gtk::ButtonBox boxTotal;
	Gtk::ButtonBox boxFloor;
	
};

class Login : public Gtk::Dialog
{
public:
	struct Credential
	{
		bool valid;
		std::string user;
		std::string name;
		muposysdb::User userdb;
	};
	Login();
	Login(const Glib::ustring& title, Gtk::Window& parent, bool modal);
	void init();
	virtual ~Login();
	
	//int run();
	const Credential& get_credential() const;
	void set_session(const char*,const char*);
	
protected:
	Gtk::Label lbMessage;
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	void on_response(int);
	
private:
	//int retcode;
	Gtk::Button btOK;
	Gtk::Button btCancel;
	Gtk::Entry inUser,inPwd;
	Gtk::Label lbUser,lbPass;
	Gtk::Box boxUser,boxPass;
	Gtk::ButtonBox boxButtons;
	
	void check_user();
	Credential credential;
};


class Main : public Gtk::Window
{
public:
	Main();
	Main(bool devel);
	/**
	*
	**/
	virtual ~Main();
	
	void set_title(const char* );
	void set_subtitle(const char* );
	void add_activity(Gtk::Widget&);
	
	static Login::Credential credential;
	
protected:
	Gtk::HeaderBar header;
	Gtk::Toolbar tbMain;
	
	void init();
	void check_session();	

#ifdef MUPOSYS_DESK_ENABLE_TDD
	//bool on_key_press_event(GdkEventKey* key_event) override;
#endif
	
private:
	Login login;
	Gtk::Label lbUser;
	bool devel;
	Gtk::VBox boxSlices;
	Gtk::Notebook nbMain;
	Gtk::Button btUserMang;
	Gtk::Button btApplication;
	Gtk::HBox box_header;
	Gtk::HBox box_header_info;
	Gtk::HBox box_header_controls;
	Gtk::Separator sep_header;
	
#ifdef MUPOSYS_DESK_ENABLE_TDD
	TableSaling sales;
	Gtk::ToolButton btSales;
#endif
};

class Restaurant : public Main
{
public:
	/**
	*
	**/
	Restaurant();
	Restaurant(bool devel);
	virtual ~Restaurant();
		
protected:
	
private:
	
};

}

#endif
