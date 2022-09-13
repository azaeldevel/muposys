

#include <chrono>


#include "http.hh"



namespace muposys::http
{

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


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



	muposys::http::db::Session& Session::getSession()
	{
		return session;
	}
	const std::string& Session::getSessionID() const
	{
		return session.getSession();
	}
	const std::string& Session::getHost() const
	{
		return host;
	}
	/*Session::Session(const std::string& id)
	{
		if(getenv("REMOTE_ADDR") == NULL)
		{
			host = "localhost";
		}
		else
		{
			host = getenv("REMOTE_ADDR");
		}
		
        //
        muposys::http::db::Conector conn(muposys::http::db::database_file);
   		conn.begin();
   		
   		if(id.empty())
   		{
			//std::cout << "empty id\n";
		   	if(session.selectByRemoteAddr(conn,host))//existe?
		   	{
				//std::cout << "exists id\n";
		  		if(session.downloadIDs(conn))
		  		{
		  			//std::cout << "Descargo : " << session.getRomoteAddress() << " - " << session.getSession()<< "\n";
		  		}
		  		else
		  		{
		  			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		  		}
		   	}
		   	else
		   	{
				addregister(conn);
		   	}
	   	}
	   	else
	   	{
	   		if(session.selectBySession(conn,id))
	   		{
	   			//std::cout << "Sesion : " << id << " encontrada <br>";
		   		if(session.downloadIDs(conn))
			  	{
			  		//std::cout << "Sesion : " << session.getID() << " datos descargados <br>";
			  	}
			  	else
			  	{
			  			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			  	}
	   		}
	   		else
	   		{
	   			addregister(conn);
	   		}
	   	}
	   	conn.commit();
	   	conn.close();
	}*/
	Session::Session()
	{
		/*if(getenv("REMOTE_ADDR") == NULL)
		{
			host = "localhost";
		}
		else
		{
			host = getenv("REMOTE_ADDR");
		}
		
        //
        muposys::http::db::Conector conn(muposys::http::db::database_file);
		if(session.selectByRemote(conn,host))//existe?
		{
		  	if(session.downloadIDs(conn))
		  	{
		  		//std::cout << "Descargo : " << session.getRomoteAddress() << " - " << session.getSession()<< "\n";
		  	}
		}*/
	}

	bool Session::load(muposys::http::db::Conector& conn)
	{
		host = getenv("REMOTE_ADDR");
		//std::cout << "host : " << host << "\n";
        //
		if(session.selectByRemote(conn,host))//existe?
		{
		  	return !session.empty();
		}
		else
		{
			return false;
		}
	}
	bool Session::addregister(muposys::http::db::Conector& conn)
	{
		//session = id;
		//std::cout << "Step 1\n";
		unsigned char digest[MD5_DIGEST_LENGTH];
		char mdString[33];
				//std::cout << "Step 2\n";
				//std::cout << "Step 3\n";
				time_t now = time(0);
				char* dt = ctime(&now);
				//std::cout << "Step 4\n";
				std::string md5semilla = host + "-";
				//std::cout << "Step 5\n";
				md5semilla += dt;
				//std::cout << "Step 6\n";
				MD5((unsigned char*)md5semilla.c_str(), strlen(md5semilla.c_str()), (unsigned char*)&digest);
				for(int i = 0; i < 16; i++)
				{
					sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
				}
				//std::cout << "mdString : " << mdString << "\n";
				//session = mdString;
				   
		   		//std::cout << "Inserted : (" << host << ") - (" << mdString << ")<br>";
		   		if(session.insert(conn,host,mdString,std::to_string(timeSinceEpochMillisec())))
		   		{
		   			//std::cout << "Inserted addr: (" << host << ") <br>";
		   			if(session.downloadIDs(conn))
			  		{
			  			return true;
			  		}
			  		else
			  		{
			  			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
						 return false;
			  		}
		   		}
		   		else
		   		{
		  			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
					return false;
		  		}

		return true;
	}
}