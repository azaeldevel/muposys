#ifndef SYSAPP_APPLICATION_SERVER
#define SYSAPP_APPLICATION_SERVER


#include "server.hh"


namespace sysapp
{

class Application : public server::elements::Html
{
private:
	server::elements::Html* html;

	
	
	bool buildHead();
	bool buildHTML();
	
public:
	virtual bool print();
	Application();
	~Application();

	class Body : public server::elements::Body
	{
	private:

	public:
		virtual bool print(std::ostream& out);
		Body();
		
	};
};

}

#endif