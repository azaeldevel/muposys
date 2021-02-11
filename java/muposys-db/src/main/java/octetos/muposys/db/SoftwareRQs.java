package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class SoftwareRQs
{
	String TABLE_NAME = "`SoftwareRQs`";

	String name;
	int number;
	String origin;
	int priority;
	SoftwareProjects project;
	String type;


	public SoftwareRQs()
	{
	}
	public SoftwareRQs(int project,int number)
	{
		this.project = new SoftwareProjects(project);
		this.number = number;
	}
	public SoftwareRQs(SoftwareRQs obj)
	{
		this.name = obj.name;
		this.number = obj.number;
		this.origin = obj.origin;
		this.priority = obj.priority;
		this.project = obj.project;
		this.type = obj.type;
	}


	public String getName()
	{
		return name;
	}

	public int getNumber()
	{
		return number;
	}

	public String getOrigin()
	{
		return origin;
	}

	public int getPriority()
	{
		return priority;
	}

	public SoftwareProjects getProject()
	{
		return project;
	}

	public String getType()
	{
		return type;
	}

	public int getProjectValue()
	{
		return project.getEnte().getID();
	}
	public int getNumberValue()
	{
		return number;
	}


	public boolean upName(octetos.db.maria.Connector connector,String name) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upOrigin(octetos.db.maria.Connector connector,String origin) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "origin = " + "'" + origin + "'";
		sqlString = sqlString + " WHERE " +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upPriority(octetos.db.maria.Connector connector,int priority) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "priority = " + priority;
		sqlString = sqlString + " WHERE " +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}
	public boolean upType(octetos.db.maria.Connector connector,String type) throws SQLException
	{
		String sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "type = " + "'" + type + "'";
		sqlString = sqlString + " WHERE " +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		return connector.update(sqlString,dt);
	}


	public boolean insert(octetos.db.maria.Connector connector,String projectName,String name,int priority) throws SQLException
	{
		this.project = new SoftwareProjects();
		if(this.project.insert(connector,projectName) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(project,number,name,priority)";
		sqlString = sqlString + " VALUES(" + project.getEnte().getID() + ","  + number + ","  +  "'"  + name + "'" + ","  + priority +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			this.number = number;
			return true;
		}
		return false;
	}
	public boolean insert(octetos.db.maria.Connector connector,SoftwareProjects project,int number,String  name,int priority) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(project,number,name,priority)";
		sqlString = sqlString + " VALUES(" + project.getEnte().getID() + ","  + number + ","  +  "'"  + name + "'" + ","  + priority +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt))
		{
			this.project = new SoftwareProjects(project);
			this.number = number;
			return true;
		}
		return false;
	}


	public static ArrayList<SoftwareRQs> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT project,number FROM SoftwareRQs WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY project,number ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY project,number DESC ";
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
			ArrayList<SoftwareRQs> tmpVc = new ArrayList<SoftwareRQs>();
			while(dt.next())
			{
				SoftwareRQs tmp = null;
				tmp = new SoftwareRQs(dt.getInt(1),dt.getInt(2));
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}
	public boolean select(octetos.db.maria.Connector connector,SoftwareProjects project,int number) throws SQLException
	{
		String sqlString = "SELECT  project, number";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dat = null;
		dat = connector.select(sqlString);
		if(dat != null)
		{
			this.project = new SoftwareProjects(project);
			this.number = number;
		}
		return dat != null;
	}


	public boolean downName(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT name  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
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
	public boolean downNumber(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT number  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			number = dt.getInt(1);
			return true;
		}
		return false;
	}
	public boolean downOrigin(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT origin  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			origin = dt.getString(1);
			return true;
		}
		return false;
	}
	public boolean downPriority(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT priority  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		dt = connector.select(sqlString);
		if(dt != null)
		{
			if(!dt.next()) return false;
			priority = dt.getInt(1);
			return true;
		}
		return false;
	}
	public boolean downType(octetos.db.maria.Connector connector) throws SQLException
	{
		String sqlString = "SELECT type  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
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
		String sqlString = "DELETE FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + project.getEnte().getID() + " and " +  "number = " + number;
		ResultSet dt = null;
		return connector.remove(sqlString,dt);
	}


}

