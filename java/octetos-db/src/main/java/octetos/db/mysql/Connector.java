
package octetos.db.mysql;


import java.sql.Connection;
import java.sql.SQLException;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

/**
 *
 * @author azael
 */
public class Connector implements octetos.db.Connector
{    
    private Connection connection;
        
    public boolean execute(String str,ResultSet rs) throws SQLException
    {
        Statement stmt = null;

        stmt = connection.createStatement();
        rs = stmt.executeQuery(str);
        
        return true;
    }
    public void close() throws SQLException
    {
        connection.close();
    }
    public boolean connect(octetos.db.Datconnect dat) throws SQLException
    {
        connection = DriverManager.getConnection("jdbc:mysql://" + dat.getHost()  + ":" + dat.getPort() + "/" + dat.getDatabase(),dat.getUser(),dat.getPassword());
        
        return connection.isValid(50000);
    }
}
