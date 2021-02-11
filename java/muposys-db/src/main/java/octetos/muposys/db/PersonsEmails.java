package octetos.muposys.db;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;


public class PersonsEmails
{
	String TABLE_NAME = "`PersonsEmails`";

	Entities ente;
	String mail;


	public PersonsEmails()
	{
	}
	public PersonsEmails(PersonsEmails obj)
	{
		this.ente = obj.ente;
		this.mail = obj.mail;
	}


	public Entities getEnte()
	{
		return ente;
	}

	public String getMail()
	{
		return mail;
	}





	public boolean insert(octetos.db.maria.Connector connector,String mail) throws SQLException
	{
		this.ente = new Entities();
		if(this.ente.insert(connector) == false) return false;
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,mail)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + mail + "'" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}
	public boolean insert(octetos.db.maria.Connector connector,Entities ente,String  mail) throws SQLException
	{
		String sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,mail)";
		sqlString = sqlString + " VALUES(" + ente.getID() + ","  +  "'"  + mail + "'" +  ")";
		ResultSet dt = null;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}


	public static ArrayList<PersonsEmails> select(octetos.db.maria.Connector connector,String where, int leng, char order)  throws SQLException
	{
		String sqlString = "SELECT ente,mail FROM PersonsEmails WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY  ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY  DESC ";
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
			ArrayList<PersonsEmails> tmpVc = new ArrayList<PersonsEmails>();
			while(dt.next())
			{
				PersonsEmails tmp = null;
				tmp = new PersonsEmails();
				tmpVc.add(tmp);
			}
			return tmpVc;
		}
		return null;
	}






}

