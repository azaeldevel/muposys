
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#ifdef MUPOSYS
	#include <apidb/muposysdb.hpp>
#else
	#include <muposys/muposysdb.hpp>
#endif


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
	~Login();
	
	int run();
	const Credential& get_credential() const;
	
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
	~Main();
	
	void check_session();
	
protected:
	const Glib::RefPtr<Gtk::Builder>& builder;

private:
	Gtk::HeaderBar* hb_muposys;
	mps::Login* login;
	Login::Credential credential;
	Gtk::Label* lbUser;
};


}

#endif
