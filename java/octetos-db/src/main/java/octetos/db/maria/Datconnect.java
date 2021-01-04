
package octetos.db.maria;

import com.mysql.cj.jdbc.MysqlDataSource;


/**
 *
 * @author azael
 */
public class Datconnect extends MysqlDataSource implements octetos.db.Datconnect  
{
    private String host;
    private String user;
    private String password;
    private String database;
    private int port;
    
    public Datconnect(MysqlDataSource d)
    {
        host = d.getServerName();
        user = d.getUser();
        password = d.getPassword();
        database = d.getDatabaseName();
        port = d.getPort();
    }
    
    /**
     * @param host
     * @param user
     * @param password
     * @param database
     * @param port 
     */
    public Datconnect(String host,String database,int port,String user,String password)
    {
        this.host = host;
        this.user = user;
        this.password = password;
        this.database = database;
        this.port = port;
    }
    public String getHost()
    {
        return host;
    }
    public String getUser()
    {
        return user;
    }
    public String getPassword()
    {
        return password;
    }
    public String getDatabase()
    {
        return database;
    }  
    public int getPort()
    {
        return port;    
    }
}
