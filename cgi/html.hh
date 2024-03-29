#ifndef MUPOSYS_HTML_HH
#define MUPOSYS_HTML_HH

#include <iostream>
#include <vector>
#include <cgicc/HTTPContentHeader.h>
#include <cgicc/HTTPRedirectHeader.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTTPResponseHeader.h>
#include <cgicc/HTTPStatusHeader.h>


#include "config.h"
#include "http.hh"

namespace muposys
{
	void contenttype(std::ostream& out,const char* content,const char* type);
	
	void doctype(std::ostream& out,const char * type);	

	/*struct ContentType
	{
		const char* content;
		const char* type;

		ContentType();
		virtual void print(std::ostream& out) const;
	};
	struct Status
	{
		unsigned short code;
		const char* brief;
	
		Status();
		Status(unsigned short);
		
		void message();
		virtual void print(std::ostream& out) const;
	};
	void status(std::ostream& out,const Status&);

	//https://www.httpdebugger.com/http/http_header.html#:~:text=The%20general%20HTTP%20header%20format,the%20end%20of%20the%20header.
	struct Header
	{
		ContentType contenttype;
		Status status;
		std::string location;

		virtual void print(std::ostream& out) const;
		virtual void print_redirect(std::ostream& out) const;

		void redirect(const std::string&);
	};*/

	struct Tag
	{
		virtual void print(std::ostream& out) const = 0;
	};

	struct meta : public Tag
	{
		std::string charset;
		std::string content;
		std::string http_equiv;
		std::string name;

		virtual void print(std::ostream& out) const;
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


	struct Head : public Tag
	{
		std::string title;
		
		std::vector<meta> metas;
		std::vector<link> links;

		virtual void print(std::ostream& out) const;

		void redirect(unsigned short time,const char* url);
		void charset(const char*);
		void responsive(const char* name,const char* content);
		void css(const char*);
		
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
	struct Body : public Tag
	{
		std::vector<script> scripts;
		 
	};
	
	class Service
	{
	public:	
		Service();
		Service(const std::filesystem::path&);		
		Service(const Datconnect&);
		Service(const std::filesystem::path&,const Datconnect&);

		~Service();
		
		bool create_session();
		bool remove_session();
		bool has_session();
		bool add(const char* varible,const char* value);
		bool add(const std::string& varible,const std::string& value);
		bool permission(const char*);
		bool open(const std::filesystem::path& );
		bool register_session(const char*);
	private:
		bool is_open_http;
		bool is_open_DB;
		
	protected:
		muposys::http::db::Conector connHttp;
		muposys::http::Session session;
		Connector connDB;
	};
	class Page : public Tag, public Service
	{
	public:
		Page();
		Page(Body&);
		Page(Body&,const std::string title);

		Page(Body&,const std::filesystem::path&);		
		Page(Body&,const Datconnect&);
		Page(Body&,const std::filesystem::path&,const Datconnect&);

		Page(Body&,const std::string& title,const std::filesystem::path&);		
		Page(Body&,const std::string& title,const Datconnect&);
		Page(Body&,const std::string& title,const std::filesystem::path&,const Datconnect&);

		
		
		virtual void print(std::ostream& out) const;
		virtual int main(std::ostream& out)  = 0;
	private:
	protected:
		Body* body; 
		Head head;
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
}


#endif