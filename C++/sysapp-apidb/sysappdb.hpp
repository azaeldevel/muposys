#include <octetos/db/clientdb-maria.hh>

#include <string>
namespace sysappdb
{
	static const octetos::db::mariadb::Datconnect datconex("localhost",3306,"sysapp.alpha","sysapp","123456");


	class Persons
	{
	private:
		static const std::string TABLE_NAME;
		std::string country;
		int id;
		std::string name1;
		std::string name2;
		std::string name3;
		std::string name4;
	public:
		const std::string& getCountry() const;
		std::string getCountryString() const;
		bool updateCountry(octetos::db::mariadb::Connector& connector,const std::string& country);
		int getID() const;
		int getKeyID() const;
		std::string getIDString() const;
		bool updateID(octetos::db::mariadb::Connector& connector,int id);
		const std::string& getName1() const;
		std::string getName1String() const;
		bool updateName1(octetos::db::mariadb::Connector& connector,const std::string& name1);
		const std::string& getName2() const;
		std::string getName2String() const;
		bool updateName2(octetos::db::mariadb::Connector& connector,const std::string& name2);
		const std::string& getName3() const;
		std::string getName3String() const;
		bool updateName3(octetos::db::mariadb::Connector& connector,const std::string& name3);
		const std::string& getName4() const;
		std::string getName4String() const;
		bool updateName4(octetos::db::mariadb::Connector& connector,const std::string& name4);
		Persons(int);
		Persons(const Persons&);
		Persons();
		bool insert(octetos::db::mariadb::Connector& connector ,std::string name1);
		static std::vector<Persons*>* select(octetos::db::mariadb::Connector& connector,const std::string& where, int leng = 0);
	};
	class Users
	{
	private:
		static const std::string TABLE_NAME;
		std::string name;
		int person;
		std::string pwdtxt;
	public:
		const std::string& getName() const;
		std::string getNameString() const;
		bool updateName(octetos::db::mariadb::Connector& connector,const std::string& name);
		int getPerson() const;
		int getKeyPerson() const;
		std::string getPersonString() const;
		bool updatePerson(octetos::db::mariadb::Connector& connector,int person);
		const std::string& getPwdtxt() const;
		std::string getPwdtxtString() const;
		bool updatePwdtxt(octetos::db::mariadb::Connector& connector,const std::string& pwdtxt);
		Users(int);
		Users(const Users&);
		Users();
		bool insert(octetos::db::mariadb::Connector& connector ,std::string name);
		static std::vector<Users*>* select(octetos::db::mariadb::Connector& connector,const std::string& where, int leng = 0);
		bool checkpass(octetos::db::mariadb::Connector& connector);
	};

}

