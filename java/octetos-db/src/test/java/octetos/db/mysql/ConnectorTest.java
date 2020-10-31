
package octetos.db.mysql;

import java.sql.ResultSet;
import octetos.db.Datconnect;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author azael
 */
public class ConnectorTest {
    
    public ConnectorTest() {
    }
    
    @BeforeAll
    public static void setUpClass() {
    }
    
    @AfterAll
    public static void tearDownClass() {
    }
    
    @BeforeEach
    public void setUp() {
    }
    
    @AfterEach
    public void tearDown() {
    }


    /**
     * Test of close method, of class Connector.
     */
    @Test
    public void testClose() throws Exception {
    }

    /**
     * Test of connect method, of class Connector.
     */
    @Test
    public void testConnect() throws Exception {
        
        octetos.db.mysql.Datconnect dat = new octetos.db.mysql.Datconnect("localhost","sysapp.alpha",3306,"sysapp","123456");
        
        octetos.db.mysql.Connector connector = new octetos.db.mysql.Connector();
        boolean checkConection = false;
        try
        {
            checkConection = connector.connect(dat);
        }
        catch(java.sql.SQLException e)            
        {
            e.printStackTrace(); 
            assertTrue(false);
        }
        assertEquals(checkConection, true);
        try
        {
            connector.close();
        }
        catch(java.sql.SQLException e)            
        {
            e.printStackTrace(); 
            assertTrue(false);
        }
    }

    /**
     * Test of execute method, of class Connector.
     */
    @Test
    public void testExecute() throws Exception {
        
    }
    
}
