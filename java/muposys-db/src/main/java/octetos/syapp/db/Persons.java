
package octetos.syapp.db;

import octetos.db.mysql.Connector;


/**
 *
 * @author azael
 */
public class Persons 
{
    private int id;
    
    
    Persons(int id)
    {
        this.id = id;
    }
    
    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

}
