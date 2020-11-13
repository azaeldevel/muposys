#ifndef SYSAPP_SERVER_HH
#define SYSAPP_SERVER_HH

#include <string>
#include <vector>


#include "http.hh"

namespace muposys::server
{

namespace elements
{

	/**
	*@brief Todo elemento html, secarateriza por no tener variable output,
	*       por tener etiqueta de apertura y cerradura en metodo print
	*/
	class Element
	{
	public:
		virtual bool print(std::ostream& out) = 0;
	};

	/**
	*@brief Secarateriza por tener variable output,
	*       por no tener etiqueta de apertura y cerradura en metodo print
	*/
	class Container
	{
	protected:
		std::ostream& out;

	public:
		virtual bool print() = 0;
		static std::ostream& getDefaultOutput();
		Container(std::ostream&);
		std::ostream& getOut();
	};
	
	/**
	*@brief Seccion head de html
	*/
	class Head : public Element
	{
	private:
		std::string title;
		std::vector<std::string> meta;
		std::vector<std::string> css;

	public:
		bool addMetaCharset(const std::string&);
		bool addMetaContent();
		bool addMetaHttpEquiv();
		bool addMetaName(const std::string& name, const std::string& content);
		void setTitle(const std::string&);
		virtual bool print(std::ostream& out);
		bool addCSS(const std::string& filename);
	};

	/**
	*@brief Seccion body de html
	*/
	class Body : public Element
	{
	};

	class Form : public Body
	{

	};
	
	class MessageDialog : public Body
	{

	};
	
	/**
	*@brief Clase base para contenedores, un hijo de esta clase represetna un mime(content-type)
	*/
	class ContentType : public Container
	{
		
	public:
		enum Text
		{
			html,
			plain
		};
		ContentType::Text contenttype;

	public:
		ContentType(std::ostream& out);		
		void  setContentType(ContentType::Text);
		bool print();
	};
	
	/**
	*@brief Representa un mime para content-ype:text/html 
	*/
	class Html : public ContentType
	{
	private:
		Head head;
		Body* body;
	public:
		Head* getHead();
		Body* getBody();
		Html(std::ostream& out);
		Html(std::ostream& out,Body* b);
		virtual bool print();
		void setBody(Body*);
	};

	class Window : public server::elements::Html
	{
	private:	
		
		bool buildHead();
		bool buildHTML();
		
	public:
		virtual bool print();
		Window(std::ostream& out,Body*);
		virtual ~Window();

	};
}


class Login
{
private:	
	muposys::http::Session* session;
	

public:
	bool check(const std::string&,const std::string&);
	const std::string& getSessionID()const;
	Login();
	Login(const std::string& sessionid);
	muposys::http::Session& getSession();
};



}

#endif