




#include "http.hh"


namespace sysapp::http
{

	const std::string& Session::getSession() const
	{
		return session;
	}
	const std::string& Session::getHost() const
	{
		return host;
	}
	Session::Session()
	{
		char mdString[33];
		char* h = getenv("REMOTE_ADDR");
		MD5((unsigned char*)h, strlen(h), (unsigned char*)&digest);
		for(int i = 0; i < 16; i++)
        {
        	sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
        }
        session = mdString;
        host = h;
        //
        sysapp::db::sqlite::Conector conn("database");
        sysapp::db::sqlite::User user;
   		conn.begin();
	   	if(user.selectByRemoteAddr(conn,host))//existe?
	   	{
	  		if(user.downloadIDs(conn))
	  		{
	  			//std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";
	  		}
	  		else
	  		{
	  			std::cout << "Fallo Descarga<br>";
	  		}
	   	}
	   	else
	   	{
	   		if(user.insert(conn,host,mdString))
	   		{
	   			//std::cout << "Inserted addr: (" << host << ") - (" << user.getID() << ")<br>";
	   		}
	   		else
	   		{
	  			std::cout << "Fail insert : " << conn.getErrorMessage() << "<br>";
	  		}
	   	}
	   	conn.commit();
	   	conn.close();
	}
	
}