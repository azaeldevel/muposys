package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class Catalog
{
	String TABLE_NAME = "`Catalog`";

	String brief;
	Entities ente;
	String number;
	String type;


	public Catalog()
	{
	}
	public Catalog(int ente)
	{
		this.ente = new Entities(ente);
	}
	public Catalog(Catalog obj)
	{
		this.brief = obj.brief;
		this.ente = obj.ente;
		this.number = obj.number;
		this.type = obj.type;
	}


	public String getBrief()
	{
		return brief;
	}

	public Entities getEnte()
	{
		return ente;
	}

	public String getNumber()
	{
		return number;
	}

	public String getType()
	{
		return type;
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
	public boolean upNumber(octetos.db.maria.Connector connector,String number) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "number = " + "'" + number + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upType(octetos.db.maria.Connector connector,String type) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "type = " + "'" + type + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}


	public boolean insert(octetos.db.maria.Connector connector,String number,String type,String brief) throws SQLException
	{
		this.ente = new Entities();
		if(this.ente.insert(connector) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,number,type,brief)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + number + "'" + ","  +  "'"  + type + "'" + ","  +  "'"  + brief + "'" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	public boolean insert(octetos.db.maria.Connector connector,Entities ente,String  number,String  type,String  brief) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,number,type,brief)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + number + "'" + ","  +  "'"  + type + "'" + ","  +  "'"  + brief + "'" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			this.ente = ente;
			return true;
		}
		return false;
	}


	public static ArrayList<Catalog> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT ente FROM Catalog WHERE ";
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
			ArrayList<Catalog> tmpVc = new ArrayList<Catalog>();
			while(dt.next())
			{
				Catalog tmp = null;
				tmp = new Catalog(dt.getInt(1));
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


	public boolean downBrief(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT brief  FROM Catalog WHERE ";
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
	public boolean downNumber(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT number  FROM Catalog WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			number = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downType(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT type  FROM Catalog WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			type = dt.getString(1);
			return true;
		}
		return false;
	}


	public boolean remove(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "DELETE FROM Catalog WHERE ";
		sqlString = sqlString +  "ente = " + ente.getID();
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

