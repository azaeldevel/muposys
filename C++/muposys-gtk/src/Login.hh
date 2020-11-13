#ifndef SYSAPP_LOGIN_HH
#define SYSAPP_LOGIN_HH

#include <gtkmm.h>
#include "../libraries/sysappdb.hpp"



class Login : public Gtk::Window
{
protected:
	Glib::RefPtr<Gtk::Builder> builder;
	Gtk::Entry* txUser;
	Gtk::Entry* txPassword;
	Gtk::Label* lbMessage;
	Gtk::Button* btAccept;
	Gtk::Button* btCancel;
    //signal handlers
    void on_accept_button_clicked();
    void on_cancel_button_clicked();

public:
	Login(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
};

#endif