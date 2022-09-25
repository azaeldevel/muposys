#include "http-db.hh"

#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>


namespace muposys
{
namespace http
{
namespace db
{
	bool Variable::remove(Conector& connect,const std::string& session)
    {
        std::string sql = "DELETE FROM  ";
        sql += TABLE_NAME + " WHERE session = '" + session + "'";
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql))
        {
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	bool Variable::remove(Conector& connect)
    {
        std::string sql = "DELETE FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id);
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql))
        {
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
   	int Variable::callbackID(void *obj, int argc, char **argv, char **azColName)
    {
        std::vector<Variable*>* vec = (std::vector<Variable*>*)obj;
        Variable* v = new Variable();        	
        v->id = std::atoi(argv[0]);	
        vec->push_back(v);
        
        return 0;
    }
	bool Variable::select(Conector& connect,const Session& s, std::vector<Variable*>& vec)
    {
        std::string sql = "SELECT id FROM  ";
        sql += TABLE_NAME + " WHERE session = ";
        sql += std::to_string(s.getID());
        if(connect.query(sql,callbackID,&vec))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	const std::string& Variable::getName()const
	{
		return name;
	}
	const std::string& Variable::getValue()const
	{
		return value;
	}
   	int Variable::callbackBySession(void *obj, int argc, char **argv, char **azColName)
    {
        Variable* p = (Variable*)obj;	
        p->id = std::atoi(argv[0]);	
        p->name = argv[1];
        p->value = argv[2];
        return 0;
    }
    bool Variable::select(Conector& connect,const Session& session, const std::string&)
    {
        std::string sql = "SELECT id,name,value FROM  ";
        sql += TABLE_NAME + " WHERE session = ";
        sql += std::to_string(session.getID());
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql,callbackBySession,this))
        {
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	bool Variable::insert(Conector& connect,const Session& s ,const std::string& n,const std::string& v)
	{
		std::string sql = "INSERT INTO ";
        sql += TABLE_NAME + "(session,name,value) VALUES('";
        sql += std::to_string(s.getID()) + "','";
        sql += n + "','" + v + "')";
        std::cout << sql << "<br>";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}

	
	bool Variable::insert(Conector& connect,const std::string& host,const std::string& n,const std::string& v)
	{
		std::string sql = "INSERT INTO ";
        sql += TABLE_NAME + "(session,name,value) VALUES('";
        sql += host + "','";
        sql += n + "','" + v + "')";
        //std::cout << sql << "<br>";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}
    bool Variable::select(Conector& connect,const std::string& host,const std::string&)
    {
        std::string sql = "SELECT id,name,value FROM ";
        sql += TABLE_NAME + " WHERE session = '";
        sql += host + "'";
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql,callbackBySession,this))
        {
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
	
	std::string Variable::TABLE_NAME = "Variables";








	Session::Session()
	{
		id = -1;
	}
	bool Session::remove(Conector& connect)
	{
		if(not Variable::remove(connect,remote_addr))
		{
			return false;
		}
		
		
        std::string sql = "DELETE FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id);
        //std::cout << "SQL: " << sql << "<br>\n";
        if(connect.query(sql))
        {
            return true;
        }
				
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		return false;
	}
	bool Session::insert(Conector& connect,const std::string& r,const std::string& s,const std::string& t)
	{
		std::string sql = "INSERT INTO ";
        sql += TABLE_NAME + "(remote_addr,session,lasttime) VALUES('";
        sql += r + "','" + s + "','" + t + "')";
        //std::cout << sql << "<br>";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}
	bool Session::updateSession(Conector& connect,const std::string& str)
	{
		std::string sql = "UPDATE  ";
        sql += TABLE_NAME + " SET session = '";
        sql += str + "' WHERE id = " + std::to_string(id) + ";";
        //std::cout << sql << "<br>";
        return connect.query(str);
	}
	const std::string& Session::getRomoteAddress()const
	{
		return remote_addr;
	}
	const std::string& Session:: getSession()const
	{
		return session;
	}
	int Session::getID()const
	{
		return id;
	}
	bool Session::insert(Conector& connect,const std::string& str)
	{
		std::string sql = "INSERT INTO  ";
        sql += TABLE_NAME + "(remote_addr,session,lasttime) VALUES('";
        sql += str + "','DEPRECATED','DEPRECATED')";
		//std::cout << "SQL : " << sql << "\n";
        if(connect.query(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
	}
   	int Session::callbackIDs(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->remote_addr = argv[0] != NULL ? argv[0] : "";	
        p->session = argv[1] != NULL ? argv[1] : "";
        
        return 0;
    }
    bool Session::downloadIDs(Conector& connect)
    {
    	//std::cout << "download id : " << id << "\n";
    	std::string sql = "SELECT remote_addr,session FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id) ;
        
        return connect.query(sql,callbackIDs,this);
    }
   	int Session::callbackBySession(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->id = std::atoi(argv[0]);	
        
        return 0;
    }
   	/*int Session::callbackBySession(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->id = std::atoi(argv[0]);	
        
        return 0;
    }*/
    bool Session::selectBySession(Conector& connect, const std::string& r)
    {
        std::string sql = "SELECT id FROM  ";
        sql += TABLE_NAME + " WHERE session = '";
        sql += r + "'";
        if(connect.query(sql,callbackBySession,this))
        {
            return true;
        }
		
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
    bool Session::selectByRemote(Conector& connect, const std::string& r)
    {
        std::string sql = "SELECT id FROM  ";
        sql += TABLE_NAME + " WHERE remote_addr = '";
        sql += r + "'";
		//std::cout << "Session::selectByRemote : " << sql << "\n";
        if(connect.query(sql,callbackByRemote,this))
        {
            return true;
        }
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
        return false;
    }
    int Session::callbackByRemote(void *obj, int argc, char **argv, char **azColName)
    {
        Session* p = (Session*)obj;	
        p->id = std::atoi(argv[0]);	        
        //std::cout << "id : " << p->id << "\n";
        return 0;
    }
	bool Session::empty() const
	{
		if(id <= 0) return true;
		return false;
	}

	
	std::string Session::TABLE_NAME = "Session";
		
		
		
		
		
		
		
		
	
	std::filesystem::path Conector::database_file = DATABASE;
		
	
    Conector::Conector() : serverConnector(NULL)
    {
    }
    Conector::Conector(const std::filesystem::path& dbname) : serverConnector(NULL)
    {
        open(dbname); 
    }
    Conector::~Conector()
    {
        if(serverConnector) close();
    }



	
	bool Conector::begin()
	{
		return query("BEGIN TRANSACTION;",NULL,NULL);
	}
	bool Conector::commit()
	{
		return query("END TRANSACTION;",NULL,NULL);
	}
	bool Conector::rollback()
	{
		return query("ROLLBACK TRANSACTION;",NULL,NULL);
	}
	int Conector::getErrorCode()const
	{
		return sqlite3_errcode((sqlite3*)serverConnector);
	}
	const char* Conector::getErrorMessage()const
	{
		return sqlite3_errmsg((sqlite3*)serverConnector);
	}
	/*bool Conector::update(const std::string& str)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), 0, 0, NULL);
        if( rc != SQLITE_OK ) 			
        {
        	std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }*/
	void Conector::close()
	{
		if(serverConnector != NULL) 
		{
			sqlite3_close((sqlite3*)serverConnector);
			serverConnector = NULL;
		}
	}
	/**
    ***
    **/
    bool Conector::query(const std::string& str)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), 0, 0, NULL);
        if( rc != SQLITE_OK ) 			
        {
        	//std::cout << "Fail : " << __FILE__ << ":" << __LINE__ << ":  " << str << "<br>";
			//std::cout << "database : " << muposys::http::db::Conector::database_file << "<br>\n";
        	std::cout << "Error SQL : " << getErrorMessage() << "<br>\n";
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }	
    /**
    ***
    **/
    bool Conector::query(const std::string& str, int (*callback)(void*,int,char**,char**),void* obj)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), callback, obj, NULL);
        if( rc != SQLITE_OK )
        {
        	//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			//std::cout << "database : " << muposys::http::db::database_file << "\n";
			std::cout << "Error SQL : " << getErrorMessage() << "<br>\n";
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }
    void* Conector::getServerConnector()
    {
        return serverConnector;
    }
    bool Conector::open(const std::filesystem::path& dbname)
    {
        int rc = sqlite3_open_v2(dbname.c_str(), (sqlite3**)&serverConnector,SQLITE_OPEN_READWRITE,NULL);
        if(SQLITE_NOTFOUND == rc)
		{
			throw muposys::Exception(muposys::Exception::FAIL_OPEN_DATABASE,__FILE__,__LINE__);
		}
		else if(rc != SQLITE_OK) 
        {
			//fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg((sqlite3*)serverConnector));
			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			throw muposys::Exception(muposys::Exception::FAIL_OPEN_DATABASE,__FILE__,__LINE__);
			//return(0);
        } 

		return true;
    }
}
}
}
