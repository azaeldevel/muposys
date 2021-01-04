package octetos.muposys.db;
import java.sql.ResultSet;import java.sql.SQLException;
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
	byte getMajor()
	{
		return major;
	}
	byte getMinor()
	{
		return minor;
	}
	public String getName()
	{
		return name;
	}
	byte getPatch()
	{
		return patch;
	}


	public boolean updateMajor(octetos.db.maria.Connector connector,byte major) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET major = " + major;
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateMinor(octetos.db.maria.Connector connector,byte minor) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET minor = " + minor;
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateName(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name = '" + name + "'";
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updatePatch(octetos.db.maria.Connector connector,byte patch) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET patch = " + patch;
		sqlString = sqlString + " WHERE ente = " + ente.getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}


	boolean insert(octetos.db.maria.Connector connector,byte major) throws SQLException
	{
		this.ente = new Entities();
		if(ente.insert(connector) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  + major + ")";
		ResultSet rs = null;
		if(connector.insert(sqlString,rs)) return true;
		return false;
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
	public static ArrayList<Versions> select(octetos.db.maria.Connector connector,String where, int leng)  throws SQLException
	{
		String sqlString = "SELECT ente FROM Versions WHERE ";
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
			ArrayList<Versions> tmpVc = new ArrayList<Versions>();
			while(rs.next())
			{
				Versions tmp;
				tmp = new Versions(rs.getInt(1));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}


	public boolean downMajor(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT major ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			major = rs.getByte(1);
			return true;
		}
		return false;
	}
	public boolean downMinor(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT minor ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			minor = rs.getByte(1);
			return true;
		}
		return false;
	}
	public boolean downName(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			name = rs.getString(1);
			return true;
		}
		return false;
	}
	public boolean downPatch(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT patch ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + ente.getID() + "'";
		ResultSet rs = null;
		rs = connector.select(sqlString);
		if(rs.next())
		{
			patch = rs.getByte(1);
			return true;
		}
		return false;
	}


}

