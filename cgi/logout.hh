
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH

#include "http.hh"
#include "html.hh"
#include <apidb/muposysdb.hpp>

namespace muposys::server
{


class Logout : public muposys::HTML
{
private:	
	bool check()const;

public:
	Logout();
	virtual ~Logout();
	

	virtual void print(std::ostream& out) const;
	virtual int main();
};


}



#endif