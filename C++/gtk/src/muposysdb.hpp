#ifndef MUPOSYSDB_HH
#include <octetos/db/clientdb-maria.hh>
#include <string>
namespace muposysdb
{
	static const octetos::db::maria::Datconnect datconex("localhost",3306,"muposys-0.1-alpha","muposys","123456");


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

		int getID() const; 
		const std::string& getMd5sum() const; 

		bool updateMd5sum(octetos::db::maria::Connector& connector,const std::string& md5sum);

		bool insert(octetos::db::maria::Connector& connector);

		bool select(octetos::db::maria::Connector& connector,int id);
		static std::vector<Entities*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1);

		bool downMd5sum(octetos::db::maria::Connector& connector);
	};
	class Persons
	{
	private:
		static const std::string TABLE_NAME;
		float age;
		float canyonLength;
		float canyonNumber;
		std::string gender;
		std::string name1;
		std::string name2;
		std::string name3;
		std::string name4;
		Entities* person;
	public:
		Persons();
		Persons(const Persons&);
		Persons(int person);

		float getAge() const; 
		float getCanyonLength() const; 
		float getCanyonNumber() const; 
		const std::string& getGender() const; 
		const std::string& getName1() const; 
		const std::string& getName2() const; 
		const std::string& getName3() const; 
		const std::string& getName4() const; 
		const Entities& getPerson() const; 

		bool updateAge(octetos::db::maria::Connector& connector,float age);
		bool updateCanyonLength(octetos::db::maria::Connector& connector,float canyonLength);
		bool updateCanyonNumber(octetos::db::maria::Connector& connector,float canyonNumber);
		bool updateGender(octetos::db::maria::Connector& connector,const std::string& gender);
		bool updateName1(octetos::db::maria::Connector& connector,const std::string& name1);
		bool updateName2(octetos::db::maria::Connector& connector,const std::string& name2);
		bool updateName3(octetos::db::maria::Connector& connector,const std::string& name3);
		bool updateName4(octetos::db::maria::Connector& connector,const std::string& name4);

		bool insert(octetos::db::maria::Connector& connector,const std::string& name1);

		bool select(octetos::db::maria::Connector& connector,const Entities& person);
		static std::vector<Persons*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1);
		static std::vector<Persons*>* selectByName(octetos::db::maria::Connector& connector,const std::string& name1,const std::string& name2, int leng = 0);

		bool downAge(octetos::db::maria::Connector& connector);
		bool downCanyonLength(octetos::db::maria::Connector& connector);
		bool downCanyonNumber(octetos::db::maria::Connector& connector);
		bool downGender(octetos::db::maria::Connector& connector);
		bool downName1(octetos::db::maria::Connector& connector);
		bool downName2(octetos::db::maria::Connector& connector);
		bool downName3(octetos::db::maria::Connector& connector);
		bool downName4(octetos::db::maria::Connector& connector);
	};
	class Users
	{
	private:
		static const std::string TABLE_NAME;
		std::string name;
		std::string pwdtxt;
		std::string status;
		Persons* user;
	public:
		Users();
		Users(const Users&);
		Users(int user);

		const std::string& getName() const; 
		const std::string& getPwdtxt() const; 
		const std::string& getStatus() const; 
		const Persons& getUser() const; 

		bool updateName(octetos::db::maria::Connector& connector,const std::string& name);
		bool updatePwdtxt(octetos::db::maria::Connector& connector,const std::string& pwdtxt);
		bool updateStatus(octetos::db::maria::Connector& connector,const std::string& status);

		bool insert(octetos::db::maria::Connector& connector,const std::string& userName1,const std::string& name);

		bool select(octetos::db::maria::Connector& connector,const Persons& user);
		static std::vector<Users*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1);
		static std::vector<Users*>* selecrUserByName(octetos::db::maria::Connector& connector,const std::string& name, int leng = 0);

		bool checkpass(octetos::db::maria::Connector& connector);
		bool downName(octetos::db::maria::Connector& connector);
		bool downPwdtxt(octetos::db::maria::Connector& connector);
		bool downStatus(octetos::db::maria::Connector& connector);
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

		const Entities& getEnte() const; 
		unsigned char getMajor() const; 
		unsigned char getMinor() const; 
		const std::string& getName() const; 
		unsigned char getPatch() const; 

		bool updateMajor(octetos::db::maria::Connector& connector,unsigned char major);
		bool updateMinor(octetos::db::maria::Connector& connector,unsigned char minor);
		bool updateName(octetos::db::maria::Connector& connector,const std::string& name);
		bool updatePatch(octetos::db::maria::Connector& connector,unsigned char patch);

		bool insert(octetos::db::maria::Connector& connector,unsigned char major);

		bool select(octetos::db::maria::Connector& connector,const Entities& ente);
		static std::vector<Versions*>* select(octetos::db::maria::Connector& connector,const std::string& where, int leng = -1);

		bool downMajor(octetos::db::maria::Connector& connector);
		bool downMinor(octetos::db::maria::Connector& connector);
		bool downName(octetos::db::maria::Connector& connector);
		bool downPatch(octetos::db::maria::Connector& connector);
	};

}

#endif
