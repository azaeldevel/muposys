#ifndef MUPOSYS_WEB_APPLICATION_HH
#define MUPOSYS_WEB_APPLICATION_HH


#include "html.hh"

namespace mps
{

class BodyApplication : public mps::Body
{
private:
	
public:
	virtual std::ostream& print (std::ostream& out);
	virtual void programs(std::ostream& out);
	virtual void panel(std::ostream& out);
	
protected:
	
};

class Application : public mps::Page
{
public:
	virtual std::ostream& print (std::ostream& out);
	virtual int main(std::ostream& out = std::cout);
	
	Application(BodyApplication&);
	Application(BodyApplication&,const std::string& title);
	void init();
	virtual ~Application();
	
private:	
	
protected:
	
};

}

#endif
