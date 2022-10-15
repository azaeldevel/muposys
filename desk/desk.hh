
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/muposysdb.hpp>

#include "Exception.hh"

namespace mps
{

#if defined DATABASE_ENGINE_MARIA
	typedef octetos::db::maria::Connector Connector;
	typedef octetos::db::maria::Datconnect Datconnect;
#elif defined DATABASE_ENGINE_MYSQL
	typedef octetos::db::mysql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
#elif defined DATABASE_ENGINE_POSTGRESQL
	typedef octetos::db::postgresql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
#else
	typedef octetos::db::Connector Connector;
#endif

	
class TableSaling : public Gtk::Box
{	
public:
	TableSaling();	
	void init();
	virtual ~TableSaling();
	
protected:
	
	void row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
	
	void treeviewcolumn_validated_on_cell_data_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_number(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	void treeviewcolumn_validated_on_cell_data_quantity(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_quantity(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	float total()const;
	
	void newrow();
	
private:
	
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();
		Gtk::TreeModelColumn<unsigned int> id;		
		Gtk::TreeModelColumn<unsigned int> item;
		Gtk::TreeModelColumn<unsigned int> quantity;
		Gtk::TreeModelColumn<bool> quantity_valid;
		Gtk::TreeModelColumn<Glib::ustring> presentation;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<bool> number_validated;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<float> cost;
		Gtk::TreeModelColumn<bool> cost_valid;
	};
	
	ModelColumns columns;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	Gtk::TreeView table;
	Gtk::Button btSave;
	Gtk::Label lbTotal,lbTotalAmount;
	Gtk::Box boxTotal;
};



class Login : public Gtk::Dialog
{
public:
	struct Credential
	{
		bool valid;
		std::string user;
		std::string name;
	};
	Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~Login();
	
	int run();
	const Credential& get_credential() const;
	void set_session(const char*,const char*);
	
protected:
	const Glib::RefPtr<Gtk::Builder>& builder;
	Gtk::Label* lbmsg;
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	void on_in_user_clean();
	bool on_in_user_enter(GdkEventKey* );
	
private:
	int retcode;
	Gtk::Button* btOK;
	Gtk::Button* btCancel;
	Gtk::Entry* inUser;
	Gtk::Entry* inPwd;
	
	void check_user();
	Credential credential;
};


class Main : public Gtk::Window
{
public:
	/**
	*
	**/
	Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool devel);
	void init();
	virtual ~Main();
	
	void check_session();	
	void add_activity(Gtk::Widget&);
	
protected:
	const Glib::RefPtr<Gtk::Builder>& builder;
	mps::Login* login;
	Gtk::HeaderBar* hb_muposys;
	//void set_title(const char* );
	//void set_subtitle(const char* );

private:
	Login::Credential credential;
	Gtk::Label* lbUser;
	bool devel;
	Gtk::Box* boxSlices;
	Gtk::Notebook* nbMain;
	
#ifdef ENABLE_DEVEL
	TableSaling sales;
#endif
};

class Restaurant : public Main
{
public:
	/**
	*
	**/
	Restaurant(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	Restaurant(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool devel);
	virtual ~Restaurant();
		
protected:
	
private:
	
};

}

#endif
