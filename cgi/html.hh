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


	struct Head : public Tag
	{
		std::vector<meta> metas;

		virtual void print(std::ostream& out) const;

		void redirect(unsigned short time,const std::string& url);
		
	};
	struct Body : public Tag
	{
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