
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
    public boolean execute(String str,ResultSet rs) throws SQLException;
}
