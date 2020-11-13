
#ifndef SYSAPP_LOGIN_SERVER
#define SYSAPP_LOGIN_SERVER


#include "server.hh"


namespace muposys
{

class Login : public server::elements::Html
{
private:
	server::elements::Html* html;
	bool flagSession;
	
	
	bool buildHead();
	bool buildHTML();
	
public:
	virtual bool print();
	Login();
	~Login();

	class Body : public server::elements::Body
	{
	private:
		const bool& flagSession;

	public:
		virtual bool print(std::ostream& out);
		Body(const bool& flagSession);
		
	};
};

}

#endif