#ifndef MUPOSYS_APPLICATION_HH
#define MUPOSYS_APPLICATION_HH

#include "http.hh"
#include "html.hh"

namespace muposys
{

class BodyApplication : public muposys::Body
{
private:
	
public:
	BodyApplication();
	BodyApplication(bool);

	virtual void print(std::ostream& out) const;
	virtual void programs(std::ostream& out) const;
	virtual void panel(std::ostream& out) const;

protected:
	bool user_mang;	
};
class Application : public muposys::Page
{	
public:
	virtual void print(std::ostream& out) const;
	virtual int main(std::ostream& out = std::cout);
	
	Application(BodyApplication&);
	Application(BodyApplication&,const std::string title);
	virtual ~Application();

private:	
	
protected:
};

}

#endif