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


	public float getAge()
	{
		return age;
	}

	public float getCanyonLength()
	{
		return canyonLength;
	}

	public float getCanyonNumber()
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

	public int getEnteValue()
	{
		return ente.getID();
	}


	public boolean upAge(octetos.db.maria.Connector connector,float age) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "age = " + age;
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upCanyonLength(octetos.db.maria.Connector connector,float canyonLength) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "canyonLength = " + canyonLength;
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upCanyonNumber(octetos.db.maria.Connector connector,float canyonNumber) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "canyonNumber = " + canyonNumber;
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upGender(octetos.db.maria.Connector connector,String gender) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "gender = " + "'" + gender + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upName1(octetos.db.maria.Connector connector,String name1) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name1 = " + "'" + name1 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upName2(octetos.db.maria.Connector connector,String name2) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name2 = " + "'" + name2 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upName3(octetos.db.maria.Connector connector,String name3) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name3 = " + "'" + name3 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upName4(octetos.db.maria.Connector connector,String name4) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name4 = " + "'" + name4 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}


	public boolean insert(octetos.db.maria.Connector connector,String name1) throws SQLException
	{
		this.ente = new Entities();
		if(this.ente.insert(connector) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name1)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + name1 + "'" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	public boolean insert(octetos.db.maria.Connector connector,Entities ente,String  name1) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name1)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + name1 + "'" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			this.ente = ente;
			return true;
		}
		return false;
	}


	public static ArrayList<Persons> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT ente FROM Persons WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY ente ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY ente DESC ";
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
			ArrayList<Persons> tmpVc = new ArrayList<Persons>();
			while(dt.next())
			{
				Persons tmp = null;
				tmp = new Persons(dt.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}
	public boolean select(octetos.db.maria.Connector connector,Entities ente) throws SQLException
	{
		String sqlString = "SELECT  ente";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "ente = " + ente.getID();
		ResultSet dat = null;
		dat = connector.select(sqlString);
		if(dat != null)
		{
			this.ente = new Entities(ente);
		}
		return dat != null;
	}


	public boolean downAge(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT age  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			age = dt.getFloat(1);
			return true;
		}
		return false;
	}
	public boolean downCanyonLength(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT canyonLength  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			canyonLength = dt.getFloat(1);
			return true;
		}
		return false;
	}
	public boolean downCanyonNumber(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT canyonNumber  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			canyonNumber = dt.getFloat(1);
			return true;
		}
		return false;
	}
	public boolean downGender(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT gender  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			gender = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName1(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name1  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			name1 = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName2(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name2  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			name2 = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName3(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name3  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			name3 = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName4(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name4  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			name4 = dt.getString(1);
			return true;
		}
		return false;
	}


	public boolean remove(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "DELETE FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

