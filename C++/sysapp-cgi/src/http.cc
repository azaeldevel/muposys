




#include "http.hh"
#include "http-db.hh"

namespace sysapp::http
{


cgicc::const_form_iterator search(cgicc::const_form_iterator first, cgicc::const_form_iterator last, const std::string& val)
{
	cgicc::const_form_iterator it = first;
  	while (it!=last) 
  	{
  		//std::cout << "Processing " << (*it).getName() << "<br>";
		if((*it).getName().compare(val) == 0)
		{
			return it;
		}
		++it;
  	}
  	return last;
}




	const std::string& Session::getSession() const
	{
		return session;
	}
	const std::string& Session::getHost() const
	{
		return host;
	}
	Session::Session(const std::string& id)
	{		
		session = id;
		
		
		unsigned char digest[MD5_DIGEST_LENGTH];
		char mdString[33];
		char* h = getenv("REMOTE_ADDR");
		time_t now = time(0);
		char* dt = ctime(&now);
        std::string md5semilla = h;
        md5semilla += dt;
		MD5((unsigned char*)md5semilla.c_str(), strlen(md5semilla.c_str()), (unsigned char*)&digest);
		for(int i = 0; i < 16; i++)
        {
        	sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
        }
        session = mdString;
        host = h;
        //
        sysapp::http::db::Conector conn("database");
        sysapp::http::db::User user;
   		conn.begin();
   		
   		if(id.empty())
   		{
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
		   		if(user.insert(conn,host,md5semilla))
		   		{
		   			//std::cout << "Inserted addr: (" << host << ") - (" << user.getID() << ")<br>";
		   		}
		   		else
		   		{
		  			std::cout << "Fail insert : " << conn.getErrorMessage() << "<br>";
		  		}
		   	}
	   	}
	   	conn.commit();
	   	conn.close();
	}
	
}