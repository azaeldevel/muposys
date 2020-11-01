

package octetos.syapp.db;

import octetos.db.mysql.Connector;
import java.sql.ResultSet;
import java.sql.SQLException;


/**
 *
 * @author azael
 */
public class Users 
{
    static private String TABLE_NAME = "Users";
    private Persons person;
    private String name;
    private String pwdtxt;
    
    
    public boolean check(Connector conn, String user,String pwd) throws SQLException
    {    
        if(select(conn, user))
        {
            if(pwdtxt.compareTo(pwd) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        return false;
    }
    public boolean select(Connector conn, String name) throws SQLException
    {
        String sql = "SELECT person, pwdtxt FROM " + TABLE_NAME + " WHERE name = '" + name + "'";
        
        ResultSet rs = conn.execute(sql);
        if(rs.next())
        {
            person = new Persons(rs.getInt(1));
            pwdtxt = rs.getString(2);
            this.name = name;
            return true;
        }
        
        return false;
    }
    
    
    

    /**
     * @return the user
     */
    public String getName() {
        return name;
    }

    /**
     * @return the pwdtxt
     */
    public String getPwdtxt() {
        return pwdtxt;
    }

    /**
     * @return the person
     */
    public Persons getPerson() {
        return person;
    }
}
