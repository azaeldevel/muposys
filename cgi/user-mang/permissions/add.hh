
#ifndef MUPOSYS_PERMISSIONS_ADD_HH
#define MUPOSYS_PERMISSIONS_ADD_HH




#include <cstdlib>
#include <iostream>
#include "cgicc/HTTPHTMLHeader.h"

#include "../../http.hh"
#include "../../html.hh"


namespace muposys::server
{


class Add : public muposys::CGI
{
private:
public:
	
	virtual int main(std::ostream& out = std::cout);
};


}



#endif