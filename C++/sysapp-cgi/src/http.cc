




#include "http.hh"


namespace sysapp::http
{

	const char* Session::getMD5() const
	{
		return (const char*)mdString;
	}
	const char* Session::getHost() const
	{
		return host;
	}
	Session::Session()
	{
		host = getenv("REMOTE_ADDR");
		MD5((unsigned char*)host, strlen(host), (unsigned char*)&digest);
		for(int i = 0; i < 16; i++)
        {
        	sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
        }
        
        //
        sysapp::db::sqlite::Conector conn("database");
        sysapp::db::sqlite::User user;
   		conn.begin();
	   	if(user.selectByRemoteAddr(conn,host))//existe?
	   	{
	  		if(user.downloadIDs(conn))
	  		{
	  			std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";
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
	   			std::cout << "Inserted addr: (" << host << ") - (" << user.getID() << ")<br>";
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