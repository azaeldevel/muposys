package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class SoftwareProjects
{
	String TABLE_NAME = "`SoftwareProjects`";

	String brief;
	Entities ente;
	String name;


	public SoftwareProjects()
	{
	}
	public SoftwareProjects(int ente)
	{
		this.ente = new Entities(ente);
	}
	public SoftwareProjects(SoftwareProjects obj)
	{
		this.brief = obj.brief;
		this.ente = obj.ente;
		this.name = obj.name;
	}


	public String getBrief()
	{
		return brief;
	}

	public Entities getEnte()
	{
		return ente;
	}

	public String getName()
	{
		return name;
	}

	public int getEnteValue()
	{
		return ente.getID();
	}


	public boolean upBrief(octetos.db.maria.Connector connector,String brief) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "brief = " + "'" + brief + "'";
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


	public boolean insert(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		this.ente = new Entities();
		if(this.ente.insert(connector) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + name + "'" +  ")";
		ResultSet dt = null;
		return connector.insert(sqlString,dt);
	}
	public boolean insert(octetos.db.maria.Connector connector,Entities ente,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + name + "'" +  ")";
		ResultSet dt = null;
		return connector.insert(sqlString,dt);
	}


	public static ArrayList<SoftwareProjects> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT ente FROM SoftwareProjects WHERE ";
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
			ArrayList<SoftwareProjects> tmpVc = new ArrayList<SoftwareProjects>();
			while(dt.next())
			{
				SoftwareProjects tmp = null;
				tmp = new SoftwareProjects(dt.getInt(1));
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


	public boolean downBrief(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT brief  FROM SoftwareProjects WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			brief = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downName(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name  FROM SoftwareProjects WHERE ";
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


	public boolean remove(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "DELETE FROM SoftwareProjects WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

