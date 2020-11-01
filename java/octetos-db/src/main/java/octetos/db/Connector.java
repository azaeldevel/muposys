
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
    public ResultSet execute(String str) throws SQLException;
}
