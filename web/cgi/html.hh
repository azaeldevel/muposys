#ifndef MUPOSYS_WEB_HTML_HH
#define MUPOSYS_WEB_HTML_HH

#include <iostream>
#include <vector>
#include <filesystem>
#include <iostream>
#include <map>


#ifdef __linux__
    #include <muposys/core/apidb.hh>
    #include <muposys/core/core.hh>
#elif defined MSYS2
    #include <muposys/core/src/apidb.hh>
    #include <muposys/core/src/core.hh>
#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

namespace mps
{
	void contenttype(std::ostream& out,const char* content,const char* type);

	void doctype(std::ostream& out,const char * type);

	struct Tag
	{
		virtual std::ostream& print (std::ostream& out) = 0;
	};

	struct meta : public Tag
	{
		std::string charset;
		std::string content;
		std::string http_equiv;
		std::string name;

		virtual std::ostream& print (std::ostream& out);
	};

	struct link
	{
		std::string crossorigin;
		std::string href;
		std::string hreflang;
		std::string media;
		std::string referrerpolicy;
		std::string rel;
		std::string sizes;
		std::string title;
		std::string type;

		virtual void print(std::ostream& out) const;
	};

	struct script
	{
		std::string async;
		std::string crossorigin;
		std::string defer;
		std::string integrity;
		std::string nomodule;
		std::string referrerpolicy;
		std::string src;
		std::string type;
		std::string content;

		virtual void print(std::ostream& out) const;

		void source(const char*);
	};

	struct Head : public Tag
	{
		std::string title;

		std::vector<meta> metas;
		std::vector<link> links;
		std::vector<script> scripts;

		virtual std::ostream& print (std::ostream& out);

		void redirect(unsigned short time,const char* url);
		void charset(const char*);
		void responsive(const char* name,const char* content);
		void css(const char*);
		void addscript(const char*);

	};

	struct Body : public Tag
	{
		std::vector<script> scripts;

	};

	class Service
	{
	public:
		Service();
		Service(const Datconnect&);
		virtual ~Service();

		bool create_session(const char*,std::string&);
		void remove_session(const char*);
		bool has_session();
		long get_session();
		bool add(const char* varible,const char* value);
		bool add(const std::string& varible,const std::string& value);
		bool permission(const char* permision,const char* user);
		bool register_session(const char*);
		std::string get_user();

		static const char* user_name_variable;
		
	private:
		//muposysdb::Variable variable;

	protected:
		bool is_open_DB;
		Connector connDB;
	};
	class Page : public Tag, public Service
	{
	public:
		Page();
		Page(Body&);
		Page(Body&,const std::string& title);
		Page(Body&,const Datconnect&);
		Page(Body&,const std::string& title,const Datconnect&);

		virtual ~Page();


		virtual std::ostream& print (std::ostream& out);
		virtual int main(std::ostream& out)  = 0;
	protected:
		Head head;
		Body* body;

	private:
	};

	class CGI : public Service
	{
	public:
		CGI();

		CGI(const std::filesystem::path&);
		CGI(const Datconnect&);
		CGI(const std::filesystem::path&,const Datconnect&);

		~CGI();

		virtual int main(std::ostream& out)  = 0;

	private:

	protected:
		Head head;
	};



	enum class EnviromentCGI
	{
		NONE,
		QUERY_STRING,
	};

	class Parameters : public std::map<std::string, std::string>
	{

	public:
		Parameters(EnviromentCGI);
		Parameters(std::istream&);

		const char* find(const char*)const;

	private:
		void build_query_string();
		void build(std::istream&);
	};

	class GetParams : public Parameters
	{
	public:
		GetParams();
	};

	class PostParams : public Parameters
	{
	public:
		PostParams();

	};

	struct Params : public GetParams
	{
		std::string session;

		Params();
		operator std::string()const;
	};

}


#endif
