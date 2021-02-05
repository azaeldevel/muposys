package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class Users
{
	String TABLE_NAME = "`Users`";

	String name;
	Persons person;
	String pwdtxt;
	String status;


	public Users()
	{
	}
	public Users(int person)
	{
		this.person = new Persons(person);
	}
	public Users(Users obj)
	{
		this.name = obj.name;
		this.person = obj.person;
		this.pwdtxt = obj.pwdtxt;
		this.status = obj.status;
	}


	public String getName()
	{
		return name;
	}

	public Persons getPerson()
	{
		return person;
	}

	public String getPwdtxt()
	{
		return pwdtxt;
	}

	public String getStatus()
	{
		return status;
	}

	public int getPersonValue()
	{
		return person.getEnte().getID();
	}


	public boolean upName(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upPwdtxt(octetos.db.maria.Connector connector,String pwdtxt) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "pwdtxt = " + "'" + pwdtxt + "'";
		sqlString = sqlString + " WHERE " +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upStatus(octetos.db.maria.Connector connector,String status) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "status = " + "'" + status + "'";
		sqlString = sqlString + " WHERE " +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}


	public boolean insert(octetos.db.maria.Connector connector,String personName1,String name) throws SQLException
	{
		this.person = new Persons();
		if(this.person.insert(connector,personName1) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(person,name)";
		sqlString = sqlString + " VALUES(" + person.getEnte().getID() + ","  +  "'"  + name + "'" +  ")";
		ResultSet dt = null;
		return connector.insert(sqlString,dt);
	}
	public boolean insert(octetos.db.maria.Connector connector,Persons person,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(person,name)";
		sqlString = sqlString + " VALUES(" + person.getEnte().getID() + ","  +  "'"  + name + "'" +  ")";
		ResultSet dt = null;
		return connector.insert(sqlString,dt);
	}


	public static ArrayList<Users> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT person FROM Users WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY person ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY person DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += leng;
		}
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			ArrayList<Users> tmpVc = new ArrayList<Users>();
			while(dt.next())
			{
				Users tmp = null;
				tmp = new Users(dt.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}
	public boolean select(octetos.db.maria.Connector connector,Persons person) throws SQLException
	{
		String sqlString = "SELECT  person";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "person = " + person.getEnte().getID();
		ResultSet dat = null;
		dat = connector.select(sqlString);
		if(dat != null)
		{
			this.person = new Persons();
		}
		return dat != null;
	}


	public boolean downName(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name  FROM Users WHERE ";
		sqlString = sqlString +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			name = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downPwdtxt(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT pwdtxt  FROM Users WHERE ";
		sqlString = sqlString +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			pwdtxt = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downStatus(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT status  FROM Users WHERE ";
		sqlString = sqlString +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			status = dt.getString(1);
			return true;
		}
		return false;
	}


	public boolean remove(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "DELETE FROM Users WHERE ";
		sqlString = sqlString +  "person = " + person.getEnte().getID();
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

