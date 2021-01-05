
package octetos.muposys.db;


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
        octetos.db.maria.Datconnect dat = new octetos.db.maria.Datconnect("localhost","muposys-0.1-alpha",3306,"muposys","123456");
        
        octetos.db.maria.Connector connector = new octetos.db.maria.Connector();
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
        boolean check = false;
        Users user = new Users(1);
        user.downName(connector);
        user.downPwdtxt(connector);
        if(user.getName().compareTo("root") == 0 && user.getPwdtxt().compareTo("123456") == 0 )
        {
            check = true;
        }
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
