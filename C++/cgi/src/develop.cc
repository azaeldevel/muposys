
#include <iostream>

#include "Mail.hh"


int main()
{
	std::cout << "Sending ...";
	muposys::SMTP smtp;
	smtp.send();
	std::cout << " sended.\n";
}
