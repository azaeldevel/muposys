
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/core/apidb.hh>
#include <gtkmm.h>
#include <muposys/core/Exception.hh>


#include "TableSaling.hh"

namespace mps
{

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
	//void add_activity(Gtk::Widget&);
	
	static Login::Credential credential;
	
protected:
	Gtk::HeaderBar header;
	Gtk::Toolbar tbMain;
	Gtk::Notebook nbMain;
	
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
	//Gtk::Button btUserMang;
	Gtk::Button btHome,btSysMang,btLogout,btAbout;
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
