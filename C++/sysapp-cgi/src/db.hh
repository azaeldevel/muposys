#ifndef SYSAPP_DB_SQLITE_HH
#define SYSAPP_DB_SQLITE_HH

#include <string>
#include <vector>

namespace sysapp
{
namespace db
{
namespace sqlite
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
        
    class User
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
        static bool selectAll(Conector& conect, std::vector<User*>& vec);
		bool downloadIDs(Conector& conect);
		bool inserteRemoteAddr(Conector& conect,const std::string&);
		bool insert(Conector& conect,const std::string&,const std::string&);
		User();
		const std::string& getRomoteAddress()const;
		const std::string& getSession()const;
		int getID()const;
		bool updateSession(Conector& connect,const std::string& str);
    };    
    
}
}
}

#endif
