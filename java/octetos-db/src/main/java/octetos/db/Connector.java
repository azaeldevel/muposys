
package octetos.db;

import java.sql.ResultSet;
import java.sql.SQLException;


/**
 *
 * @author azael
 */
public interface Connector 
{   
    public boolean connect(Datconnect connector) throws SQLException;
    public void close()throws SQLException;
    public ResultSet execute(String str,ResultSet rs) throws SQLException;
    public boolean update(String str,ResultSet rs) throws SQLException;
    public ResultSet select(String str) throws SQLException;
    public boolean insert(String str,ResultSet rs) throws SQLException;
    public boolean delete(String str,ResultSet rs) throws SQLException;
}
