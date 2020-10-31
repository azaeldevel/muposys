
package octetos.db;

/**
 *
 * @author azael
 */
public interface Datconnect 
{
    public abstract String getHost();
    public abstract String getUser();
    public abstract String getPassword();
    public abstract String getDatabase();
    public abstract int getPort();
}
