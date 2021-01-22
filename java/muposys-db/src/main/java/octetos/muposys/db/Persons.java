package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class Persons
{
	String TABLE_NAME = "`Persons`";

	float age;
	float canyonLength;
	float canyonNumber;
	Entities ente;
	String gender;
	String name1;
	String name2;
	String name3;
	String name4;


	public Persons()
	{
	}
	public Persons(int ente)
	{
		this.ente = new Entities(ente);
	}
	public Persons(Persons obj)
	{
		this.age = obj.age;
		this.canyonLength = obj.canyonLength;
		this.canyonNumber = obj.canyonNumber;
		this.ente = obj.ente;
		this.gender = obj.gender;
		this.name1 = obj.name1;
		this.name2 = obj.name2;
		this.name3 = obj.name3;
		this.name4 = obj.name4;
	}


	float getAge()
	{
		return age;
	}
	float getCanyonLength()
	{
		return canyonLength;
	}
	float getCanyonNumber()
	{
		return canyonNumber;
	}
	public Entities getEnte()
	{
		return ente;
	}
	public String getGender()
	{
		return gender;
	}
	public String getName1()
	{
		return name1;
	}
	public String getName2()
	{
		return name2;
	}
	public String getName3()
	{
		return name3;
	}
	public String getName4()
	{
		return name4;
	}


	public boolean updateAge(octetos.db.maria.Connector connector,float age) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET age = " + age;
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateCanyonLength(octetos.db.maria.Connector connector,float canyonLength) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET canyonLength = " + canyonLength;
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateCanyonNumber(octetos.db.maria.Connector connector,float canyonNumber) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET canyonNumber = " + canyonNumber;
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateGender(octetos.db.maria.Connector connector,String gender) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET gender = '" + gender + "'";
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateName1(octetos.db.maria.Connector connector,String name1) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name1 = '" + name1 + "'";
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateName2(octetos.db.maria.Connector connector,String name2) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name2 = '" + name2 + "'";
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateName3(octetos.db.maria.Connector connector,String name3) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name3 = '" + name3 + "'";
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateName4(octetos.db.maria.Connector connector,String name4) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name4 = '" + name4 + "'";
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}


	public boolean insert(octetos.db.maria.Connector connector,String name1) throws SQLException
	{
                //System.out.println("Persons::insert Step 1");
		ente = new Entities();
                //System.out.println("Persons::insert Step 2");
		if(ente.insert(connector) == false) return false;
                //System.out.println("Persons::insert Step 3");
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name1)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + name1 + "'" +  ")";
		ResultSet dt = null;
                //System.out.println("Persons::insert Step 4");
		return connector.insert(sqlString,dt);
	}


	public boolean select(octetos.db.maria.Connector connector,Entities ente) throws SQLException
	{
		String sql = "SELECT  ente";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		rs = connector.select(sql);
		if(rs != null)
		{
			this.ente = new Entities(ente);
			return true;
		}
		return false;
	}
	public static ArrayList<Persons> select(octetos.db.maria.Connector connector,String where, int leng)  throws SQLException
	{
		String sqlString = "SELECT ente FROM Persons WHERE ";
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
			ArrayList<Persons> tmpVc = new ArrayList<Persons>();
			while(rs.next())
			{
				Persons tmp;
				tmp = new Persons(rs.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}


	public boolean downAge(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT age ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			age = rs.getFloat(1);
			return true;
		}
		return false;
	}
	public boolean downCanyonLength(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT canyonLength ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			canyonLength = rs.getFloat(1);
			return true;
		}
		return false;
	}
	public boolean downCanyonNumber(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT canyonNumber ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			canyonNumber = rs.getFloat(1);
			return true;
		}
		return false;
	}
	public boolean downGender(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT gender ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			gender = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName1(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name1 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			name1 = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName2(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name2 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			name2 = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName3(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name3 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			name3 = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName4(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name4 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			name4 = rs.getString(1);
			return true;
		}
		return false;
	}


}

