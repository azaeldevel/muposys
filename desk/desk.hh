
#ifndef MUPOSYS_MAIN_HH
#define MUPOSYS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

namespace mps
{

class Main : public Gtk::Window
{
public:
/**
*
**/
	Main(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Main();

protected:
	const Glib::RefPtr<Gtk::Builder>& builder;

	void on_bt_close_clicked();


private:
	Gtk::HeaderBar* hb_muposys;
	Gtk::Button* bt_close;
};

class Food : public Main
{
public:
	/**
	*
	**/
	Food(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Food();
	
private:

};


class Pizza : public Food
{
public:
	/**
	*
	**/
	Pizza(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	~Pizza();
	
private:

};

}

#endif
