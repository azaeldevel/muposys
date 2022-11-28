#ifndef SYSAPP_DB_SQLITE_HH
#define SYSAPP_DB_SQLITE_HH


#include "config.h"

#include <string>
#include <vector>
#include <filesystem>
#include <muposys/apidb.hh>

#include "Exception.hh"


namespace muposys
{

#if defined DATABASE_ENGINE_MARIA
	typedef octetos::db::maria::Connector Connector;
	typedef octetos::db::maria::Datconnect Datconnect;
#elif defined DATABASE_ENGINE_MYSQL
	typedef octetos::db::mysql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
#elif defined DATABASE_ENGINE_POSTGRESQL
	typedef octetos::db::postgresql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
#else
	typedef octetos::db::Connector Connector;
#endif

namespace http
{
namespace db
{
	class Variable;
	
	std::string remote_host();
	
    class Conector
    {
    private:
        void* serverConnector;
		
    public:

        Conector();
		/**
		*@brief Crean una conexion a la base de dato indicada
		*@param filename Nombre de archivo de la base de datos.
		*/
        Conector(const std::filesystem::path& filename);
        ~Conector();

		/**
		*@brief Realiza una consula
		*@return true si la consulta se completo satisfactoriamente(incluso si no returna registros), falso si hubo un error. 
		*/
        bool query(const std::string&,int (*callback)(void*,int,char**,char**),void* obj);

		/**
		*@brief Realiza una consula
		*@return true si la consulta se completo satisfactoriamente(incluso si no returna registros), falso si hubo un error. 
		*/
		bool query(const std::string&);
		//bool update(const std::string&);
        void* getServerConnector();
		void close();
		const char* getErrorMessage()const;
		int getErrorCode()const;
		bool begin();
		bool commit();
		bool rollback();
		bool open(const std::filesystem::path& filename);


		static std::filesystem::path database_file;
    };
    
	/**
	*@brief Tabla principal para almacenar la informacion de sesion.
	*
	*/
    class Session
    {
	private:
		static std::string TABLE_NAME;
        int id;
		std::string remote_addr;
		std::string session;
        
        static int callbackBySession(void *data, int argc, char **argv, char **azColName);
        static int callbackByRemote(void *data, int argc, char **argv, char **azColName);
		static int callbackIDs(void *data, int argc, char **argv, char **azColName);
			
    public:
		Session();

        bool selectByRemote(Conector& conect, const std::string&);
		bool selectBySession(Conector& conect, const std::string&);
        static bool selectAll(Conector& conect, std::vector<Session*>& vec);
		bool downloadIDs(Conector& conect);
		bool insert(Conector& conect,const std::string&);
		[[deprecated]] bool insert(Conector& conect,const std::string& remote_addr,const std::string& session,const std::string& lasttime);

		const std::string& getRomoteAddress()const;
		const std::string& getSession()const;
		int getID()const;
		bool updateSession(Conector& connect,const std::string& str);
		bool remove(Conector& connect);
		bool empty()const;
		/**
		*@brief Modifica el valor de la variable indicada
		*@return true si existe y escribe el valor, falso en otro caso.
		*/
		bool setVariable(Conector& conect,const std::string& name,const std::string& value);
		/**
		*@brief Agrega una variable a la tabla de variable para esta sesion
		*@return true si crea la variable, falso si ya existe
		*/
		bool addVariable(Conector& conect,const std::string& name,const std::string& value);
		/**
		*@brief Busca y retuna una variable
		*@return true si encuentra la variable, falso en otro caso.
		*/
		bool getVariable(Conector& conect,const std::string& name, Variable&);
		/**
		*@brief Busca todas las variables asignadas a esta session
		*@return true si encuentra alguna, falso en otro caso.
		*/
		bool getVariables(Conector& conect, std::vector<Variable*>& vec);
    }; 

	  
	class Variable
	{
	private:
		static std::string TABLE_NAME;
        int id;
		std::string name;
		std::string value;
		
		static int callbackBySession(void *data, int argc, char **argv, char **azColName);
		static int callbackID(void *data, int argc, char **argv, char **azColName);
    public:
		int getID() const;
		[[deprecated]] bool insert(Conector& conect,const Session& session,const std::string& name,const std::string& value);
		[[deprecated]] bool select(Conector& conect,const Session& session, const std::string& name);
		const std::string& getName()const;
		const std::string& getValue()const;
		bool remove(Conector& connect);
		[[deprecated]] static bool select(Conector& conect,const Session& session, std::vector<Variable*>& vec);
		static bool remove(Conector& connect,const std::string& session);
		bool updateValue(Conector& connect,const Session& session,const std::string& name,const std::string& value);


		bool insert(Conector& conect,const std::string& session,const std::string& name,const std::string& value);
		bool select(Conector& conect,const std::string& host,const std::string& name);
	};    
}
}
}

#endif
