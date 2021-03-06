#ifndef MUPOSYSDB_HPP
#define MUPOSYSDB_HPP
#include <octetos/db/clientdb-maria.hh>
#include <string>

namespace muposysdb
{
	class Catalog;
	class Entities;
	class Persons;
	class PersonsEmails;
	class SoftwareProjects;
	class SoftwareRQs;
	class Stock;
	class Users;
	class Versions;

}
namespace muposysdb
{


	static const octetos::db::maria::Datconnect datconex("localhost",3306,"muposys-0.1-alpha","muposys","123456");


	class Catalog
	{
	private:
		static const std::string TABLE_NAME;
		std::string brief;
		Entities* ente;
		std::string number;
		std::string type;
	public:
		Catalog();
		Catalog(const Catalog&);
		Catalog(int ente);
		~Catalog();


		const std::string& getBrief() const; 
		Entities& getEnte() const; 
		const std::string& getNumber() const; 
		const std::string& getType() const; 
		int getEnteValue() const; 

		bool upBrief(octetos::db::maria::Connector& connector,const std::string& brief);
		bool upNumber(octetos::db::maria::Connector& connector,const std::string& number);
		bool upType(octetos::db::maria::Connector& connector,const std::string& type);

		bool insert(octetos::db::maria::Connector& connector,const std::string& number,const std::string& type,const std::string& brief);
		bool insert(octetos::db::maria::Connector& connector,const Entities& ente,const std::string& number,const std::string& type,const std::string& brief);

		static std::vector<Catalog*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& ente);

		bool downBrief(octetos::db::maria::Connector& connector);
		bool downNumber(octetos::db::maria::Connector& connector);
		bool downType(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class Entities
	{
	private:
		static const std::string TABLE_NAME;
		int id;
		std::string md5sum;
	public:
		Entities();
		Entities(const Entities&);
		Entities(int id);
		~Entities();


		int getID() const; 
		const std::string& getMd5sum() const; 
		int getIDValue() const; 

		bool upMd5sum(octetos::db::maria::Connector& connector,const std::string& md5sum);

		bool insert(octetos::db::maria::Connector& connector);

		static std::vector<Entities*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,int id);

		bool downMd5sum(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class Persons
	{
	private:
		static const std::string TABLE_NAME;
		float age;
		float canyonLength;
		float canyonNumber;
		Entities* ente;
		std::string gender;
		std::string name1;
		std::string name2;
		std::string name3;
		std::string name4;
	public:
		Persons();
		Persons(const Persons&);
		Persons(int ente);
		~Persons();


		float getAge() const; 
		float getCanyonLength() const; 
		float getCanyonNumber() const; 
		Entities& getEnte() const; 
		const std::string& getGender() const; 
		const std::string& getName1() const; 
		const std::string& getName2() const; 
		const std::string& getName3() const; 
		const std::string& getName4() const; 
		int getEnteValue() const; 

		bool upAge(octetos::db::maria::Connector& connector,float age);
		bool upCanyonLength(octetos::db::maria::Connector& connector,float canyonLength);
		bool upCanyonNumber(octetos::db::maria::Connector& connector,float canyonNumber);
		bool upGender(octetos::db::maria::Connector& connector,const std::string& gender);
		bool upName1(octetos::db::maria::Connector& connector,const std::string& name1);
		bool upName2(octetos::db::maria::Connector& connector,const std::string& name2);
		bool upName3(octetos::db::maria::Connector& connector,const std::string& name3);
		bool upName4(octetos::db::maria::Connector& connector,const std::string& name4);

		bool insert(octetos::db::maria::Connector& connector,const std::string& name1);
		bool insert(octetos::db::maria::Connector& connector,const Entities& ente,const std::string& name1);

		static std::vector<Persons*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		static std::vector<Persons*>* selectByName(octetos::db::maria::Connector& connector,const std::string& name1,const std::string& name2, int leng = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& ente);

		bool downAge(octetos::db::maria::Connector& connector);
		bool downCanyonLength(octetos::db::maria::Connector& connector);
		bool downCanyonNumber(octetos::db::maria::Connector& connector);
		bool downGender(octetos::db::maria::Connector& connector);
		bool downName1(octetos::db::maria::Connector& connector);
		bool downName2(octetos::db::maria::Connector& connector);
		bool downName3(octetos::db::maria::Connector& connector);
		bool downName4(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class PersonsEmails
	{
	private:
		static const std::string TABLE_NAME;
		Entities* ente;
		std::string mail;
	public:
		PersonsEmails();
		PersonsEmails(const PersonsEmails&);
		~PersonsEmails();


		Entities& getEnte() const; 
		const std::string& getMail() const; 


		bool insert(octetos::db::maria::Connector& connector,const std::string& mail);
		bool insert(octetos::db::maria::Connector& connector,const Entities& ente,const std::string& mail);

		static std::vector<PersonsEmails*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector);

		bool downMail(octetos::db::maria::Connector& connector);

	};
	class SoftwareProjects
	{
	private:
		static const std::string TABLE_NAME;
		std::string brief;
		Entities* ente;
		std::string name;
	public:
		SoftwareProjects();
		SoftwareProjects(const SoftwareProjects&);
		SoftwareProjects(int ente);
		~SoftwareProjects();


		const std::string& getBrief() const; 
		Entities& getEnte() const; 
		const std::string& getName() const; 
		int getEnteValue() const; 

		bool upBrief(octetos::db::maria::Connector& connector,const std::string& brief);
		bool upName(octetos::db::maria::Connector& connector,const std::string& name);

		bool insert(octetos::db::maria::Connector& connector,const std::string& name);
		bool insert(octetos::db::maria::Connector& connector,const Entities& ente,const std::string& name);

		static std::vector<SoftwareProjects*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& ente);

		bool downBrief(octetos::db::maria::Connector& connector);
		bool downName(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class SoftwareRQs
	{
	private:
		static const std::string TABLE_NAME;
		std::string name;
		int number;
		std::string origin;
		int priority;
		SoftwareProjects* project;
		std::string type;
	public:
		SoftwareRQs();
		SoftwareRQs(const SoftwareRQs&);
		SoftwareRQs(int project,int number);
		~SoftwareRQs();


		const std::string& getName() const; 
		int getNumber() const; 
		const std::string& getOrigin() const; 
		int getPriority() const; 
		SoftwareProjects& getProject() const; 
		const std::string& getType() const; 
		int getProjectValue() const; 
		int getNumberValue() const; 

		bool upName(octetos::db::maria::Connector& connector,const std::string& name);
		bool upOrigin(octetos::db::maria::Connector& connector,const std::string& origin);
		bool upPriority(octetos::db::maria::Connector& connector,int priority);
		bool upType(octetos::db::maria::Connector& connector,const std::string& type);

		bool insert(octetos::db::maria::Connector& connector,const std::string& projectName,const std::string& name,int priority);
		bool insert(octetos::db::maria::Connector& connector,const SoftwareProjects& project,int number,const std::string& name,int priority);

		static std::vector<SoftwareRQs*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const SoftwareProjects& project,int number);

		bool downName(octetos::db::maria::Connector& connector);
		bool downNumber(octetos::db::maria::Connector& connector);
		bool downOrigin(octetos::db::maria::Connector& connector);
		bool downPriority(octetos::db::maria::Connector& connector);
		bool downType(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class Stock
	{
	private:
		static const std::string TABLE_NAME;
		Catalog* item;
		std::string number;
		std::string position;
		int quantity;
		std::string warehouse;
	public:
		Stock();
		Stock(const Stock&);
		Stock(int item);
		~Stock();


		Catalog& getItem() const; 
		const std::string& getNumber() const; 
		const std::string& getPosition() const; 
		int getQuantity() const; 
		const std::string& getWarehouse() const; 
		int getItemValue() const; 

		bool upNumber(octetos::db::maria::Connector& connector,const std::string& number);
		bool upPosition(octetos::db::maria::Connector& connector,const std::string& position);
		bool upQuantity(octetos::db::maria::Connector& connector,int quantity);
		bool upWarehouse(octetos::db::maria::Connector& connector,const std::string& warehouse);

		bool insert(octetos::db::maria::Connector& connector,const std::string& itemNumber,const std::string& itemType,const std::string& itemBrief,const std::string& number);
		bool insert(octetos::db::maria::Connector& connector,const Catalog& item,const std::string& number);

		static std::vector<Stock*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Catalog& item);

		bool downNumber(octetos::db::maria::Connector& connector);
		bool downPosition(octetos::db::maria::Connector& connector);
		bool downQuantity(octetos::db::maria::Connector& connector);
		bool downWarehouse(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class Users
	{
	private:
		static const std::string TABLE_NAME;
		std::string name;
		Persons* person;
		std::string pwdtxt;
		std::string status;
	public:
		Users();
		Users(const Users&);
		Users(int person);
		~Users();


		const std::string& getName() const; 
		Persons& getPerson() const; 
		const std::string& getPwdtxt() const; 
		const std::string& getStatus() const; 
		int getPersonValue() const; 

		bool upName(octetos::db::maria::Connector& connector,const std::string& name);
		bool upPwdtxt(octetos::db::maria::Connector& connector,const std::string& pwdtxt);
		bool upStatus(octetos::db::maria::Connector& connector,const std::string& status);

		bool insert(octetos::db::maria::Connector& connector,const std::string& personName1,const std::string& name);
		bool insert(octetos::db::maria::Connector& connector,const Persons& person,const std::string& name);

		static std::vector<Users*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		static std::vector<Users*>* selecrUserByName(octetos::db::maria::Connector& connector,const std::string& name, int leng = 0);
		bool select(octetos::db::maria::Connector& connector,const Persons& person);

		bool checkpass(octetos::db::maria::Connector& connector);
		bool downName(octetos::db::maria::Connector& connector);
		bool downPwdtxt(octetos::db::maria::Connector& connector);
		bool downStatus(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class Versions
	{
	private:
		static const std::string TABLE_NAME;
		Entities* ente;
		unsigned char major;
		unsigned char minor;
		std::string name;
		unsigned char patch;
	public:
		Versions();
		Versions(const Versions&);
		Versions(int ente);
		~Versions();


		Entities& getEnte() const; 
		unsigned char getMajor() const; 
		unsigned char getMinor() const; 
		const std::string& getName() const; 
		unsigned char getPatch() const; 
		int getEnteValue() const; 

		bool upMajor(octetos::db::maria::Connector& connector,unsigned char major);
		bool upMinor(octetos::db::maria::Connector& connector,unsigned char minor);
		bool upName(octetos::db::maria::Connector& connector,const std::string& name);
		bool upPatch(octetos::db::maria::Connector& connector,unsigned char patch);

		bool insert(octetos::db::maria::Connector& connector,unsigned char major);
		bool insert(octetos::db::maria::Connector& connector,const Entities& ente,unsigned char major);

		static std::vector<Versions*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& ente);

		bool downMajor(octetos::db::maria::Connector& connector);
		bool downMinor(octetos::db::maria::Connector& connector);
		bool downName(octetos::db::maria::Connector& connector);
		bool downPatch(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};

}

#endif
