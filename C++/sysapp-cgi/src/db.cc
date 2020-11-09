#include "db.hh"

#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>


namespace sysapp
{
namespace db
{
namespace sqlite
{
	
	bool User::insert(Conector& connect,const std::string& h,const std::string& s)
	{
		std::string sql = "INSERT INTO ";
        sql += TABLE_NAME + "(remote_addr,session) VALUES('";
        sql += h + "','" + s + "')";
        if(connect.insert(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
				
        return false;
	}
	bool User::updateSession(Conector& connect,const std::string& str)
	{
		std::string sql = "UPDATE  ";
        sql += TABLE_NAME + " SET session = '";
        sql += str + "' WHERE id = " + std::to_string(id) + ";";
        std::cout << sql << "<br>";
        return connect.update(str);
	}
	const std::string& User::getRomoteAddress()const
	{
		return remote_addr;
	}
	const std::string&User:: getSession()const
	{
		return session;
	}
	int User::getID()const
	{
		return id;
	}
	User::User()
	{
		id = -1;
	}
	bool User::inserteRemoteAddr(Conector& connect,const std::string& str)
	{
		std::string sql = "INSERT INTO  ";
        sql += TABLE_NAME + "(remote_addr) VALUES('";
        sql += str + "')";
        if(connect.insert(sql))
        {
        	id = sqlite3_last_insert_rowid((sqlite3*)connect.getServerConnector());
            return true;
        }
				
        return false;
	}
   	int User::callbackIDs(void *obj, int argc, char **argv, char **azColName)
    {
        User* p = (User*)obj;	
        p->remote_addr = argv[0] != NULL ? argv[0] : "";	
        p->session = argv[1] != NULL ? argv[1] : "";
        
        return 0;
    }
    bool User::downloadIDs(Conector& connect)
    {
    	//std::cout << "download id : " << id << "\n";
    	std::string sql = "SELECT remote_addr,session FROM  ";
        sql += TABLE_NAME + " WHERE id = ";
        sql += std::to_string(id) ;
        //std::cout << sql << "\n";
        return connect.query(sql,callbackIDs,this);
    }
   	int User::callbackBySession(void *obj, int argc, char **argv, char **azColName)
    {
        User* p = (User*)obj;	
        p->id = std::atoi(argv[0]);	
        
        return 0;
    }
    bool User::selectBySession(Conector& connect, const std::string& r)
    {
        std::string sql = "SELECT id FROM  ";
        sql += TABLE_NAME + " WHERE session = '";
        sql += r + "'";
        if(connect.query(sql,callbackBySession,this))
        {
            return true;
        }
			
        return false;
    }
    int User::callbackByRemoteAddr(void *obj, int argc, char **argv, char **azColName)
    {
        User* p = (User*)obj;	
        p->id = std::atoi(argv[0]);	        
        //std::cout << "id : " << p->id << "\n";
        return 0;
    }
    bool User::selectByRemoteAddr(Conector& connect, const std::string& r)
    {
        std::string sql = "SELECT id FROM ";
        sql += TABLE_NAME + " WHERE remote_addr = '";
        sql += r + "'";
        bool ret =  connect.query(sql,callbackByRemoteAddr,this);
        if(ret == false) return false;
        
        if(id < 0) return false;
        return true;
    }
	
	std::string User::TABLE_NAME = "Session";
		
		
		
		
		
		
		
		
		
		
		
	
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
	bool Conector::update(const std::string& str)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), 0, 0, NULL);
        if( rc != SQLITE_OK ) 			
        {
            return false;			
        } 
        else 
        {
            return true;			
        }			
    }
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
    bool Conector::insert(const std::string& str)
    {
        int rc = sqlite3_exec((sqlite3*)serverConnector, str.c_str(), 0, 0, NULL);
        if( rc != SQLITE_OK ) 			
        {
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
    Conector::~Conector()
    {
        close();
    }		
    Conector::Conector(const std::string& dbname)
    {
        serverConnector = NULL;
        int rc = sqlite3_open(dbname.c_str(), (sqlite3**)&serverConnector);
        if( rc ) {
				fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg((sqlite3*)serverConnector));
				//return(0);
        } else {
				//fprintf(stderr, "Opened database(%s) successfully\n",dbname.c_str());
        }
    }
}
}
}
