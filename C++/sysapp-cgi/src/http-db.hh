#ifndef SYSAPP_DB_SQLITE_HH
#define SYSAPP_DB_SQLITE_HH

#include <string>
#include <vector>

namespace sysapp
{
namespace http
{
namespace db
{
    class Conector
    {
    private:
        void* serverConnector;
    public:
        Conector(const std::string&);
        ~Conector();
        bool query(const std::string&,int (*callback)(void*,int,char**,char**),void* obj);
		bool insert(const std::string&);
		bool update(const std::string&);
        void* getServerConnector();
		void close();
		const char* getErrorMessage()const;
		int getErrorCode()const;
		bool begin();
		bool commit();
		bool rollback();
    };
        
    class Session
    {
	private:
		static std::string TABLE_NAME;
        int id;
		std::string remote_addr;
		std::string session;
        
        static int callbackBySession(void *data, int argc, char **argv, char **azColName);
        static int callbackByRemoteAddr(void *data, int argc, char **argv, char **azColName);
		static int callbackIDs(void *data, int argc, char **argv, char **azColName);
			
    public:
        bool selectByRemoteAddr(Conector& conect, const std::string&);
		bool selectBySession(Conector& conect, const std::string&);
        static bool selectAll(Conector& conect, std::vector<Session*>& vec);
		bool downloadIDs(Conector& conect);
		bool inserteRemoteAddr(Conector& conect,const std::string&);
		bool insert(Conector& conect,const std::string&,const std::string&);
		Session();
		const std::string& getRomoteAddress()const;
		const std::string& getSession()const;
		int getID()const;
		bool updateSession(Conector& connect,const std::string& str);
    }; 

	  
	class Variable
	{
	private:
		static std::string TABLE_NAME;
        int id;
		std::string name;
		std::string value;
		
		static int callbackBySession(void *data, int argc, char **argv, char **azColName);
    public:
		int getID() const;
		bool insert(Conector& conect,const Session& session,const std::string& name,const std::string& value);
		bool select(Conector& conect,const Session& session, const std::string& name);
		const std::string& getName()const;
		const std::string& getValue()const;
	};
    
}
}
}

#endif
