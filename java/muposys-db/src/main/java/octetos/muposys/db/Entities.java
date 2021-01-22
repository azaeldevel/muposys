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


	int getID()
	{
		return id;
	}
	public String getMd5sum()
	{
		return md5sum;
	}


	public boolean updateMd5sum(octetos.db.maria.Connector connector,String md5sum) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET md5sum = '" + md5sum + "'";
		sqlString = sqlString + " WHERE id = " + id;
		ResultSet rs = null;
		return connector.update(sqlString,rs);
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


	public boolean select(octetos.db.maria.Connector connector,int id) throws SQLException
	{
		String sql = "SELECT  id";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE id = " + id;
		ResultSet rs = null;
		rs = connector.select(sql);
		if(rs != null)
		{
			this.id = id;
			return true;
		}
		return false;
	}
	public static ArrayList<Entities> select(octetos.db.maria.Connector connector,String where, int leng)  throws SQLException
	{
		String sqlString = "SELECT id FROM Entities WHERE ";
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
			ArrayList<Entities> tmpVc = new ArrayList<Entities>();
			while(rs.next())
			{
				Entities tmp;
				tmp = new Entities(rs.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}


	public boolean downMd5sum(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT md5sum ";
		sqlString = sqlString + " FROM Entities WHERE ";
		sqlString = sqlString + "id = " + id;
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			md5sum = rs.getString(1);
			return true;
		}
		return false;
	}


}

