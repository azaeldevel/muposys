
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

namespace mps
{

class Login : public Gtk::Dialog
{
public:
	Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Login();
	
	int run();
	
protected:
	const Glib::RefPtr<Gtk::Builder>& builder;
	Gtk::Label* lbmsg;
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	
private:
	int retcode;
	Gtk::Button* btOK;
	Gtk::Button* btCancel;
};


class Main : public Gtk::Window
{
public:
	/**
	*
	**/
	Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Main();
	
	void check();
	
protected:
	const Glib::RefPtr<Gtk::Builder>& builder;
	void on_bt_close_clicked();


private:
	Gtk::HeaderBar* hb_muposys;
	Gtk::Button* bt_close;
};


}

#endif
