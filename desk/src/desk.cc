
#include <gtkmm/application.h>

#include "desk.hh"

namespace mps
{

Login::Credential Main::credential;
Main::Main() : devel(false)
{	
	hide();
	init();
		
	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
	show();
}
Main::Main(bool d) : devel(false)
{	
	init();
		
	signal_show().connect(sigc::mem_fun(*this,&Main::check_session));
	show();
}
void Main::init()
{	
	if(is_visible()) throw Exception(Exception::VISIBLE_MAIN,__FILE__,__LINE__);
	
	add_events(Gdk::KEY_PRESS_MASK);		
	
	header.set_title("Multi-Porpuse Software System");
	header.set_subtitle("muposys");
	header.set_show_close_button(true);
	set_titlebar(header);
	
	header.pack_start(box_header);
	box_header.pack_start(box_header_controls);
	box_header.pack_start(sep_header);
	box_header.pack_start(box_header_info);
	
	box_header_info.pack_start(lbUser);
	
	box_header_controls.pack_start(btApplication);
	box_header_controls.pack_start(btUserMang);
	btUserMang.set_image_from_icon_name("gtk-preferences");
	btApplication.set_image_from_icon_name("gtk-preferences");
		
#ifdef MUPOSYS_DESK_ENABLE_TDD
	//add_activity(sales);	
	//set_valign(Gtk::ALIGN_CENTER);
	//nbMain->set_valign(Gtk::ALIGN_CENTER);
	//sales.set_size_request(get_width()/3,-1);
	set_default_size(800,640);	
	show_all_children();
#endif
	
	/*
	boxSlices = 0;
	builder->get_widget("boxSlices", boxSlices);	
	
	nbMain = 0;
	builder->get_widget("nbMain", nbMain);
	*/
}
Main::~Main()
{
}

void Main::check_session()
{
	login.set_transient_for(*this);
	if(devel) login.set_session("root","123456");
	int res = Gtk::RESPONSE_NONE;
	do
	{
		res = login.run();
		switch(res)
		{
		case Gtk::RESPONSE_OK:
			break;	
		case Gtk::RESPONSE_CANCEL:
			login.close();
			return;	
		case Gtk::RESPONSE_NONE:
			break;			
		}
	}
	while(not login.get_credential().valid);
	
	if(login.get_credential().valid)
	{
		credential = login.get_credential();
		Connector connDB;
		bool flag = false;
		int res = 0;
		try
		{
			flag = connDB.connect(muposysdb::datconex);
		}
		catch(const std::exception& e)
		{
			Gtk::MessageDialog dlg(*this,"Error detectado.",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text(e.what());
			res = dlg.run();
			return;		
		}
		if(credential.userdb.downName(connDB)) lbUser.set_text(credential.userdb.getName());			
		if(credential.userdb.downPerson(connDB))
		{
			credential.userdb.getPerson().downName1(connDB);	
			credential.userdb.getPerson().downName3(connDB);	
		}
		connDB.close();
	}
	login.close();
}

/*
void Main::set_title(const char* )
{
}
void Main::set_subtitle(const char* )
{
}
*/

void Main::add_activity(Gtk::Widget& w)
{
	//nbMain->append_page(w);	
}

#ifdef MUPOSYS_DESK_ENABLE_TDD
/*
bool Main::on_key_press_event(GdkEventKey* key_event)
{
	std::cout << "key " << (char) key_event->keyval << "\n";
	
	return true;
}
*/
#endif


Login::Login()
{
	init();
}
Login::Login(const Glib::ustring& t, Gtk::Window& p, bool m) : Gtk::Dialog(t,p,m)
{
	init();
}
void Login::init()
{
	get_vbox()->pack_start(boxUser,false,true);
	get_vbox()->pack_start(boxPass,false,true);
	get_vbox()->pack_start(lbMessage,false,true);
	get_vbox()->pack_start(boxButtons,false,true);
	
	lbUser.set_text("Usuario         : ");
	boxUser.pack_start(lbUser);
	boxUser.pack_start(inUser);
	
	lbPass.set_text("Constraseña : ");
	boxPass.pack_start(lbPass);
	boxPass.pack_start(inPwd);
	inPwd.set_visibility(false);
	
	boxButtons.pack_start(btOK);
	boxButtons.pack_start(btCancel);
	
	btCancel.signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_cancel_clicked));
	btOK.signal_clicked().connect(sigc::mem_fun(*this,&Login::on_bt_ok_clicked));
	signal_response().connect(sigc::mem_fun(*this, &Login::on_response) );
	
	btOK.set_image_from_icon_name("gtk-ok");
	btCancel.set_image_from_icon_name("gtk-cancel");
	
	set_default_size(250,100);	
	show_all_children();
}
Login::~Login()
{
}
void Login::on_bt_cancel_clicked()
{
	response(Gtk::RESPONSE_CANCEL);
}
void Login::on_bt_ok_clicked()
{
	check_user();
	response(Gtk::RESPONSE_OK);
}
void Login::check_user()
{
	Connector connDB;
	bool flag = false;
	int res = 0;
	try
	{
		flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		Gtk::MessageDialog dlg(*this,"Error detectado.",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		res = dlg.run();
		return;	
	}
	
	credential.valid = true;
	
	std::string strwhere = "name = ";
	strwhere += "'" + inUser.get_text() + "' and pwdtxt = '" + inPwd.get_text() + "' and status = 'A'";
	std::vector<muposysdb::User*>* userlst = muposysdb::User::select(connDB,strwhere);
	
	//std::cout << "SQL str : " << strwhere << "\n";
	
	if(userlst == NULL) 
	{
		credential.valid = false;
		std::cout << "No hay resultado de la consulta\n";
	}
	if(userlst->size() == 0) 
	{		
		credential.valid = false;
		std::cout << "Hay 0 resultados de la consulta\n";
	}
	if(userlst->size() > 1) 
	{
		credential.valid = false;
		std::cout << "Hay " <<  userlst->size() << " resultados de la consulta\n";
	}	
	
	if(not credential.valid)//si no es valido el usario liberar memorio y salir
	{
		lbMessage.set_text("Usuario/Contraseña incorrectos.");
		for(auto u : *userlst)
		{
			u->downPerson(connDB);
			if(u->getPerson().downName1(connDB))
			{
				if(u->getPerson().downName3(connDB))
				{
					credential.name = u->getPerson().getName1() + " " + u->getPerson().getName3();
				}
			}
			else
			{
				credential.name = u->getPerson().getName1();
			}
			delete u;
		}
		delete userlst;		
		return;
	}
	//std::cout << "Usuario aceptado\n";
	credential.user = inUser.get_text();
	credential.userdb = *userlst->front();
}
const Login::Credential& Login::get_credential() const
{
	return credential;
}
void Login::set_session(const char* u,const char* p)
{	
	inUser.set_text(u);
	inPwd.set_text(p);	
}
void Login::on_response(int res)
{
	if(credential.valid and res == Gtk::RESPONSE_OK)
	{
		hide();
	}
	else
	{
		switch (res)
		{
		case Gtk::RESPONSE_CLOSE:
		case Gtk::RESPONSE_CANCEL:
		case Gtk::RESPONSE_DELETE_EVENT:
			hide();
			break;
		}
	}
}




/*Restaurant::Restaurant(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Main(cobject,refGlade)
{
}
Restaurant::Restaurant(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool d) : Main(cobject,refGlade,d)
{
}*/
Restaurant::~Restaurant()
{
}












}

