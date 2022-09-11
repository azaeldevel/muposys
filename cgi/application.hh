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
	virtual void print(std::ostream& out) const;
	virtual void options(std::ostream& out) const;	
};
class Application2 : public muposys::HTML
{	
public:
	virtual void print(std::ostream& out) const;
	virtual int main();
	
	Application2(const BodyApplication& );
	~Application2();

private:	
	
};

}

#endif