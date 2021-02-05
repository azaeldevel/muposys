package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class Entities
{
	String TABLE_NAME = "`Entities`";

	int id;
	String md5sum;


	public Entities()
	{
	}
	public Entities(int id)
	{
		this.id = id;
	}
	public Entities(Entities obj)
	{
		this.id = obj.id;
		this.md5sum = obj.md5sum;
	}


	public int getID()
	{
		return id;
	}

	public String getMd5sum()
	{
		return md5sum;
	}

	public int getIDValue()
	{
		return id;
	}


	public boolean upMd5sum(octetos.db.maria.Connector connector,String md5sum) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "md5sum = " + "'" + md5sum + "'";
		sqlString = sqlString + " WHERE " +  "id = " + id;
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}


	public boolean insert(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "()";
		sqlString = sqlString + " VALUES(" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			id = connector.last_inserted_id();
			if(id > 0) return true;
		}
		return false;
	}


	public static ArrayList<Entities> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT id FROM Entities WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY id ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY id DESC ";
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
			ArrayList<Entities> tmpVc = new ArrayList<Entities>();
			while(dt.next())
			{
				Entities tmp = null;
				tmp = new Entities(dt.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}
	public boolean select(octetos.db.maria.Connector connector,int id) throws SQLException
	{
		String sqlString = "SELECT  id";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "id = " + id;
		ResultSet dat = null;
		dat = connector.select(sqlString);
		if(dat != null)
		{
			this.id = id;
		}
		return dat != null;
	}


	public boolean downMd5sum(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT md5sum  FROM Entities WHERE ";
		sqlString = sqlString +  "id = " + id;
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			md5sum = dt.getString(1);
			return true;
		}
		return false;
	}


	public boolean remove(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "DELETE FROM Entities WHERE ";
		sqlString = sqlString +  "id = " + id;
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

