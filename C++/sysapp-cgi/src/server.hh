#ifndef SYSAPP_SERVER_HH
#define SYSAPP_SERVER_HH

#include <string>
#include <vector>


#include "http.hh"

namespace sysapp::server
{

namespace elements
{

	/**
	*@brief Todo elemento html
	*/
	class Element
	{
	public:
		virtual bool print(std::ostream& out) = 0;
	};

	/**
	*@brief Pricipalmente tiene un obejto para imprimir la salida
	*/
	class Container
	{
	protected:
		std::ostream& out;

	public:
		virtual bool print() = 0;
		virtual std::ostream& getDefaultOutput();
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
		
	public:
		bool addMetaCharset(const std::string&);
		bool addMetaContent();
		bool addMetaHttpEquiv();
		bool addMetaName(const std::string& name, const std::string& content);
		void setTitle(const std::string&);
		virtual bool print(std::ostream& out);
	};

	/**
	*@brief Seccion body de html
	*/
	class Body : public Element
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
		
	public:
		ContentType(std::ostream& out);
	};
	
	/**
	*@brief Representa un mime para content-ype:text/html 
	*/
	class HTML : public ContentType
	{
	private:
		Head head;
		Body* body;
	public:
		Head* getHead();
		Body* getBody();
		HTML(std::ostream& out);
		virtual bool print();
		void setBody(Body*);
	};

	class Content
	{
	protected:
		std::ostream& out;

	public:
		Content();
		HTML& createHtmlPage();
		ContentType* contentType(ContentType::Text);
	};
}


class Login
{
private:	
	sysapp::http::Session session;
	

public:
	bool check(const std::string&,const std::string&);
	const std::string& getSession()const;
};

}

#endif