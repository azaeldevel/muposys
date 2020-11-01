
package octetos.syapp.db;

import octetos.db.mysql.Connector;
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
public class UsersTest {
    
    public UsersTest() {
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
     * Test of check method, of class Users.
     */
    @Test
    public void testCheck() throws Exception {
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
        
        
        Users user = new Users();
        boolean check = user.check(connector, "root", "123456");
        assertTrue(check);
               
        
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
     * Test of select method, of class Users.
     */
    @Test
    public void testSelect() throws Exception {
    }

    /**
     * Test of getUser method, of class Users.
     */
    @Test
    public void testGetUser() {
    }

    /**
     * Test of getPwdtxt method, of class Users.
     */
    @Test
    public void testGetPwdtxt() {
    }

    /**
     * Test of getPerson method, of class Users.
     */
    @Test
    public void testGetPerson() {
    }
    
}
