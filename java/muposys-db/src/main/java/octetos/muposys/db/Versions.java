package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class Versions
{
	String TABLE_NAME = "`Versions`";

	Entities ente;
	byte major;
	byte minor;
	String name;
	byte patch;


	public Versions()
	{
	}
	public Versions(int ente)
	{
		this.ente = new Entities(ente);
	}
	public Versions(Versions obj)
	{
		this.ente = obj.ente;
		this.major = obj.major;
		this.minor = obj.minor;
		this.name = obj.name;
		this.patch = obj.patch;
	}


	public Entities getEnte()
	{
		return ente;
	}

	public byte getMajor()
	{
		return major;
	}

	public byte getMinor()
	{
		return minor;
	}

	public String getName()
	{
		return name;
	}

	public byte getPatch()
	{
		return patch;
	}

	public int getEnteValue()
	{
		return ente.getID();
	}


	public boolean upMajor(octetos.db.maria.Connector connector,byte major) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "major = " + major;
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upMinor(octetos.db.maria.Connector connector,byte minor) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "minor = " + minor;
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upName(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upPatch(octetos.db.maria.Connector connector,byte patch) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "patch = " + patch;
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}


	public boolean insert(octetos.db.maria.Connector connector,byte major) throws SQLException
	{
		this.ente = new Entities();
		if(this.ente.insert(connector) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  + major +  ")";
		ResultSet dt = null;
		return connector.insert(sqlString,dt);
	}
	public boolean insert(octetos.db.maria.Connector connector,Entities ente,byte major) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  + major +  ")";
		ResultSet dt = null;
		return connector.insert(sqlString,dt);
	}


	public static ArrayList<Versions> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT ente FROM Versions WHERE ";
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
			ArrayList<Versions> tmpVc = new ArrayList<Versions>();
			while(dt.next())
			{
				Versions tmp = null;
				tmp = new Versions(dt.getInt(1));
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
			this.ente = new Entities();
		}
		return dat != null;
	}


	public boolean downMajor(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT major  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			major = dt.getByte(0);
			return true;
		}
		return false;
	}
	public boolean downMinor(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT minor  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			minor = dt.getByte(0);
			return true;
		}
		return false;
	}
	public boolean downName(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
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
	public boolean downPatch(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT patch  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			patch = dt.getByte(0);
			return true;
		}
		return false;
	}


	public boolean remove(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "DELETE FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

