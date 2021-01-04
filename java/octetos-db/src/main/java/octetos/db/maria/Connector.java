
package octetos.db.maria;


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
      
    public int last_inserted_id()
    {
        return 0;
    }
    @Override
    public boolean delete(String str,ResultSet rs) throws SQLException
    {
        Statement stmt = null;

        stmt = connection.createStatement();
        rs = stmt.executeQuery(str);
        if(rs != null) return true;
        return false;        
    }
    @Override
    public ResultSet select(String str) throws SQLException
    {
        Statement stmt = null;

        stmt = connection.createStatement();
        return stmt.executeQuery(str);   
    }
    @Override
    public boolean update(String str,ResultSet rs) throws SQLException
    {
        Statement stmt = null;

        stmt = connection.createStatement();
        rs = stmt.executeQuery(str);
        if(rs != null) return true;
        return false;
        
    }
    @Override
    public boolean insert(String str,ResultSet rs) throws SQLException
    {
        Statement stmt = null;

        stmt = connection.createStatement();
        rs = stmt.executeQuery(str);
        if(rs != null) return true;
        return false;
        
    }
    @Override
    public ResultSet execute(String str,ResultSet rs) throws SQLException
    {
        Statement stmt = null;

        stmt = connection.createStatement();
        return stmt.executeQuery(str);
        
    }
    @Override
    public void close() throws SQLException
    {
        connection.close();
    }
    @Override
    public boolean connect(octetos.db.Datconnect dat) throws SQLException
    {
        connection = DriverManager.getConnection("jdbc:mysql://" + dat.getHost()  + ":" + dat.getPort() + "/" + dat.getDatabase(),dat.getUser(),dat.getPassword());
        
        return connection.isValid(50000);
    }
}
