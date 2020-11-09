#ifndef SYSAPP_SERVER_HH
#define SYSAPP_SERVER_HH

#include <string>
#include <vector>


#include "http.hh"

namespace sysapp::server
{

namespace elements
{
	class Element
	{
	public:
		virtual bool print(std::ostream& out) = 0;
	};

	class Container
	{
	public:
		virtual bool print() = 0;
	};
	
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

	class Body : public Element
	{
		
	public:
		virtual bool print(std::ostream& out);
	};


	/*class Page
	{
	private:
		HTML html;

	public:
		enum ContentType
		{
			TEXT
		};
		
		HTML& getHTML();

	private:
		ContentType contentType;

	};*/

	class ContentType : public Container
	{
	protected:
		std::ostream& out;
		
	public:
		enum Text
		{	
			html,
			plain
		};
		
	public:
		ContentType(std::ostream& out);
	};
	
	class HTML : public ContentType
	{
	private:
		Head head;
		Body body;
	public:
		Head* getHead();
		Body* getBody();
		HTML(std::ostream& out);
		virtual bool print();
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