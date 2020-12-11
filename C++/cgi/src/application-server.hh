#ifndef SYSAPP_APPLICATION_SERVER
#define SYSAPP_APPLICATION_SERVER


#include "server.hh"


namespace muposys
{

class Application : public server::elements::Window
{
private:
	
	
	bool buildHead();
	bool buildHTML();
	
public:
	class Body : public server::elements::Body
	{
	private:

	public:
		virtual bool print(std::ostream& out);
		Body();
		
	};



	virtual bool print();
	Application();
	~Application();

};

}

#endif