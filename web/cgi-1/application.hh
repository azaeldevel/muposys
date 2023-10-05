#ifndef MUPOSYS_WEB_APPLICATION_HH
#define MUPOSYS_WEB_APPLICATION_HH


#include "html.hh"

namespace oct::mps::v1
{
class Application;


class BodyApplication : public Body
{
private:
	const Params& params;

public:
	BodyApplication(const Params&);

	virtual std::ostream& print (std::ostream& out);
	virtual void programs(std::ostream& out);
	virtual void panel(std::ostream& out);

	void set(cave::mmsql::Connection& connDB);
	void set(Application&);

protected:
	cave::mmsql::Connection* connDB;
	Application* application;

};

class Application : public Page
{
public:
	virtual std::ostream& print (std::ostream& out);
	virtual int main(std::ostream& out = std::cout);

	Application(BodyApplication&,const Params&);
	Application(BodyApplication&,const std::string& title,const Params&);
	void init();
	virtual ~Application();

private:
	const Params& params;

protected:

};

}

#endif
