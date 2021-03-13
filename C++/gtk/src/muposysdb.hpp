#ifndef MUPOSYSDB_HPP
#define MUPOSYSDB_HPP
#include <octetos/db/clientdb-maria.hh>
#include <string>

namespace muposysdb
{
	class Buys;
	class CatalogClient;
	class CatalogSupplier;
	class Entities;
	class Movements;
	class Persons;
	class Stock;
	class Supplier;
	class Users;
	class Versions;

}
namespace muposysdb
{


	static const octetos::db::maria::Datconnect datconex("localhost",3306,"muposys","muposys","123456");


	class Buys
	{
	private:
		static const std::string TABLE_NAME;
		Entities* doc;
		Supplier* supplier;
	public:
		Buys();
		Buys(const Buys&);
		Buys(int doc);
		~Buys();


		Entities& getDoc() const; 
		Supplier& getSupplier() const; 
		int getDocValue() const; 

		bool upSupplier(octetos::db::maria::Connector& connector, const Supplier& supplier);

		bool insert(octetos::db::maria::Connector& connector,int supplierNumber,const std::string& supplierNameShort);
		bool insert(octetos::db::maria::Connector& connector,const Entities& doc,const Supplier& supplier);

		static std::vector<Buys*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& doc);


		bool remove(octetos::db::maria::Connector& connector);
	};
	class CatalogClient
	{
	private:
		static const std::string TABLE_NAME;
		std::string brief;
		Entities* item;
		std::string number;
		std::string ref1;
		std::string type;
	public:
		CatalogClient();
		CatalogClient(const CatalogClient&);
		CatalogClient(int item);
		~CatalogClient();


		const std::string& getBrief() const; 
		Entities& getItem() const; 
		const std::string& getNumber() const; 
		const std::string& getRef1() const; 
		const std::string& getType() const; 
		int getItemValue() const; 

		bool upBrief(octetos::db::maria::Connector& connector,const std::string& brief);
		bool upNumber(octetos::db::maria::Connector& connector,const std::string& number);
		bool upRef1(octetos::db::maria::Connector& connector,const std::string& ref1);
		bool upType(octetos::db::maria::Connector& connector,const std::string& type);

		bool insert(octetos::db::maria::Connector& connector,const std::string& number,const std::string& type,const std::string& brief);
		bool insert(octetos::db::maria::Connector& connector,const Entities& item,const std::string& number,const std::string& type,const std::string& brief);

		static std::vector<CatalogClient*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& item);

		bool downBrief(octetos::db::maria::Connector& connector);
		bool downNumber(octetos::db::maria::Connector& connector);
		bool downRef1(octetos::db::maria::Connector& connector);
		bool downType(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class CatalogSupplier
	{
	private:
		static const std::string TABLE_NAME;
		std::string brief;
		std::string factoryID;
		Entities* item;
		std::string number;
		std::string providerID;
		std::string ref1;
		std::string type;
	public:
		CatalogSupplier();
		CatalogSupplier(const CatalogSupplier&);
		CatalogSupplier(int item);
		~CatalogSupplier();


		const std::string& getBrief() const; 
		const std::string& getFactoryID() const; 
		Entities& getItem() const; 
		const std::string& getNumber() const; 
		const std::string& getProviderID() const; 
		const std::string& getRef1() const; 
		const std::string& getType() const; 
		int getItemValue() const; 

		bool upBrief(octetos::db::maria::Connector& connector,const std::string& brief);
		bool upFactoryID(octetos::db::maria::Connector& connector,const std::string& factoryID);
		bool upNumber(octetos::db::maria::Connector& connector,const std::string& number);
		bool upProviderID(octetos::db::maria::Connector& connector,const std::string& providerID);
		bool upRef1(octetos::db::maria::Connector& connector,const std::string& ref1);
		bool upType(octetos::db::maria::Connector& connector,const std::string& type);

		bool insert(octetos::db::maria::Connector& connector,const std::string& number,const std::string& type,const std::string& brief);
		bool insert(octetos::db::maria::Connector& connector,const Entities& item,const std::string& number,const std::string& type,const std::string& brief);

		static std::vector<CatalogSupplier*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& item);

		bool downBrief(octetos::db::maria::Connector& connector);
		bool downFactoryID(octetos::db::maria::Connector& connector);
		bool downNumber(octetos::db::maria::Connector& connector);
		bool downProviderID(octetos::db::maria::Connector& connector);
		bool downRef1(octetos::db::maria::Connector& connector);
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
	class Movements
	{
	private:
		static const std::string TABLE_NAME;
		int delta;
		std::string direction;
		Entities* doc;
		Entities* id;
		CatalogSupplier* item;
		int source;
	public:
		Movements();
		Movements(const Movements&);
		Movements(int id);
		~Movements();


		int getDelta() const; 
		const std::string& getDirection() const; 
		Entities& getDoc() const; 
		Entities& getID() const; 
		CatalogSupplier& getItem() const; 
		int getSource() const; 
		int getIDValue() const; 

		bool upDelta(octetos::db::maria::Connector& connector,int delta);
		bool upDirection(octetos::db::maria::Connector& connector,const std::string& direction);
		bool upDoc(octetos::db::maria::Connector& connector, const Entities& doc);
		bool upItem(octetos::db::maria::Connector& connector, const CatalogSupplier& item);
		bool upSource(octetos::db::maria::Connector& connector,int source);

		bool insert(octetos::db::maria::Connector& connector,int source,const std::string& itemNumber,const std::string& itemType,const std::string& itemBrief,int delta);
		bool insert(octetos::db::maria::Connector& connector,const Entities& id,int source,const CatalogSupplier& item,int delta,const Entities& doc);

		static std::vector<Movements*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& id);

		bool downDelta(octetos::db::maria::Connector& connector);
		bool downDirection(octetos::db::maria::Connector& connector);
		bool downSource(octetos::db::maria::Connector& connector);

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
	class Stock
	{
	private:
		static const std::string TABLE_NAME;
		int item;
		std::string number;
		std::string position;
		int quantity;
		std::string warehouse;
	public:
		Stock();
		Stock(const Stock&);
		Stock(int item);
		~Stock();


		int getItem() const; 
		const std::string& getNumber() const; 
		const std::string& getPosition() const; 
		int getQuantity() const; 
		const std::string& getWarehouse() const; 
		int getItemValue() const; 

		bool upNumber(octetos::db::maria::Connector& connector,const std::string& number);
		bool upPosition(octetos::db::maria::Connector& connector,const std::string& position);
		bool upQuantity(octetos::db::maria::Connector& connector,int quantity);
		bool upWarehouse(octetos::db::maria::Connector& connector,const std::string& warehouse);

		bool insert(octetos::db::maria::Connector& connector,const std::string& number);

		static std::vector<Stock*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,int item);

		bool downItem(octetos::db::maria::Connector& connector);
		bool downNumber(octetos::db::maria::Connector& connector);
		bool downPosition(octetos::db::maria::Connector& connector);
		bool downQuantity(octetos::db::maria::Connector& connector);
		bool downWarehouse(octetos::db::maria::Connector& connector);

		bool remove(octetos::db::maria::Connector& connector);
	};
	class Supplier
	{
	private:
		static const std::string TABLE_NAME;
		std::string nameShort;
		int number;
		Entities* supplier;
	public:
		Supplier();
		Supplier(const Supplier&);
		Supplier(int supplier);
		~Supplier();


		const std::string& getNameShort() const; 
		int getNumber() const; 
		Entities& getSupplier() const; 
		int getSupplierValue() const; 

		bool upNameShort(octetos::db::maria::Connector& connector,const std::string& nameShort);
		bool upNumber(octetos::db::maria::Connector& connector,int number);

		bool insert(octetos::db::maria::Connector& connector,int number,const std::string& nameShort);
		bool insert(octetos::db::maria::Connector& connector,const Entities& supplier,int number,const std::string& nameShort);

		static std::vector<Supplier*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1,char order = 0);
		bool select(octetos::db::maria::Connector& connector,const Entities& supplier);

		bool downNameShort(octetos::db::maria::Connector& connector);
		bool downNumber(octetos::db::maria::Connector& connector);

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
