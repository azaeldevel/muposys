#ifndef MUPOSYS_HTML_HH
#define MUPOSYS_HTML_HH

#include <iostream>
#include <vector>


namespace muposys
{
	void contenttype(std::ostream& out,const char* content,const char* type);
	
	void doctype(std::ostream& out,const char * type);	



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
	
		
	class HTML : public Tag
	{
	public:
		HTML();
		HTML(const Body&);

		
		Head head;
		
		virtual void print(std::ostream& out) const;
		virtual void main()  = 0;
	private:
		const Body* body; 
	};
	
}


#endif