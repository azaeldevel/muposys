package octetos.muposys.db;
import java.sql.ResultSet;import java.sql.SQLException;
import java.util.ArrayList;


public class Users
{
	String TABLE_NAME = "`Users`";

	String name;
	String pwdtxt;
	String status;
	Persons user;


	public Users()
	{
	}
	public Users(int user)
	{
		this.user = new Persons(user);
	}
	public Users(Users obj)
	{
		this.name = obj.name;
		this.pwdtxt = obj.pwdtxt;
		this.status = obj.status;
		this.user = obj.user;
	}


	public String getName()
	{
		return name;
	}
	public String getPwdtxt()
	{
		return pwdtxt;
	}
	public String getStatus()
	{
		return status;
	}
	public Persons getUser()
	{
		return user;
	}


	public boolean updateName(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name = '" + name + "'";
		sqlString = sqlString + " WHERE user = " + user.getPerson().getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updatePwdtxt(octetos.db.maria.Connector connector,String pwdtxt) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET pwdtxt = '" + pwdtxt + "'";
		sqlString = sqlString + " WHERE user = " + user.getPerson().getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}
	public boolean updateStatus(octetos.db.maria.Connector connector,String status) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET status = '" + status + "'";
		sqlString = sqlString + " WHERE user = " + user.getPerson().getID();
		ResultSet rs = null;
		return connector.update(sqlString,rs);
	}


	boolean insert(octetos.db.maria.Connector connector,String userName1,String name) throws SQLException
	{
		this.user = new Persons();
		if(user.insert(connector,userName1) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(user,name)";
		sqlString = sqlString + " VALUES(" + user.getPerson().getID() + ","  + "'" + name + "'" + ")";
		ResultSet rs = null;
		if(connector.insert(sqlString,rs)) return true;
		return false;
	}


	public boolean select(octetos.db.maria.Connector connector,Persons user) throws SQLException
	{
		String sql = "SELECT  user";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE user = " + user.getPerson().getID();
		ResultSet rs = null;
		rs = connector.select(sql);
		if(rs != null)
		{
			this.user = new Persons(user);
			return true;
		}
		return false;
	}
	public static ArrayList<Users> select(octetos.db.maria.Connector connector,String where, int leng)  throws SQLException
	{
		String sqlString = "SELECT user FROM Users WHERE ";
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
		sqlString = sqlString + "user = " +  "'" + user.getPerson().getID() + "'";
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
		sqlString = sqlString + "user = " +  "'" + user.getPerson().getID() + "'";
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
		sqlString = sqlString + "user = " +  "'" + user.getPerson().getID() + "'";
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

