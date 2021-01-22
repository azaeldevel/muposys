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


	public boolean updateName(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name = '" + name + "'";
		sqlString = sqlString + " WHERE person = " + person.getEnte().getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updatePwdtxt(octetos.db.maria.Connector connector,String pwdtxt) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET pwdtxt = '" + pwdtxt + "'";
		sqlString = sqlString + " WHERE person = " + person.getEnte().getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateStatus(octetos.db.maria.Connector connector,String status) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET status = '" + status + "'";
		sqlString = sqlString + " WHERE person = " + person.getEnte().getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}


	public boolean insert(octetos.db.maria.Connector connector,String personName1,String name) throws SQLException
	{
                //System.out.println("Users::insert Step 1");
		person = new Persons();
                //System.out.println("Users::insert Step 2");
		if(person.insert(connector,personName1) == false) return false;
                //System.out.println("Users::insert Step 3");
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(person,name)";
		sqlString = sqlString + " VALUES(" + person.getEnte().getID() + ","  +  "'"  + name + "'" +  ")";
		ResultSet dt = null;
                //System.out.println("Users::insert Step 4");
		return connector.insert(sqlString,dt);
	}


	public boolean select(octetos.db.maria.Connector connector,Persons person) throws SQLException
	{
		String sql = "SELECT  person";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE person = " + person.getEnte().getID();
		ResultSet rs = null;
		rs = connector.select(sql);
		if(rs != null)
		{
			this.person = new Persons(person);
			return true;
		}
		return false;
	}
	public static ArrayList<Users> select(octetos.db.maria.Connector connector,String where, int leng)  throws SQLException
	{
		String sqlString = "SELECT person FROM Users WHERE ";
		sqlString += where;
		if(leng > 0)
		{
			sqlString += " LIMIT  ";
			sqlString += leng;
 		}
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs != null)
		{
			ArrayList<Users> tmpVc = new ArrayList<Users>();
			while(rs.next())
			{
				Users tmp;
				tmp = new Users(rs.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}


	public boolean downName(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name ";
		sqlString = sqlString + " FROM Users WHERE ";
		sqlString = sqlString + "person = " +  "'" + person.getEnte().getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			name = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downPwdtxt(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT pwdtxt ";
		sqlString = sqlString + " FROM Users WHERE ";
		sqlString = sqlString + "person = " +  "'" + person.getEnte().getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			pwdtxt = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downStatus(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT status ";
		sqlString = sqlString + " FROM Users WHERE ";
		sqlString = sqlString + "person = " +  "'" + person.getEnte().getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			status = rs.getString(1);
			return true;
		}
		return false;
	}


}

