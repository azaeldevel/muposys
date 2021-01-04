
package octetos.db;


import java.sql.SQLException;

/**
 *
 * @author azael
 */
public class Datresult 
{
    java.sql.ResultSet rs;
    
    
    public boolean nextRow() throws SQLException
    {
        return true;
    }
}
