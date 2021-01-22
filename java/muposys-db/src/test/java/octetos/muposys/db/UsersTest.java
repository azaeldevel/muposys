
package octetos.muposys.db;


import java.util.ArrayList;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Random;


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

    @Test
    public void testsuid() throws Exception 
    {
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
        
        Random rand = new Random(); 
        int r = rand.nextInt(10000);
        
        String userstr,name,userstr2,name2;
        
        userstr = "user-";
        userstr += r;
        name = "name-";
        name += r;
        Users user = new Users();
        if(user.insert(connector,userstr,name))
        {
            //System.out.println("insert : " + name);
            assertTrue(true);
        }
        else
        {
            System.err.println("Fail : " + name);
            assertTrue(false);
        }
        
        r = rand.nextInt(10000);
        userstr2 = "user-";
        userstr2 += r;
        name2 = "name-";
        name2 += r;
        Users user2 = new Users();
        if(user2.insert(connector,userstr2,name2))
        {
            //System.out.println("insert : " + name2);
            assertTrue(true);
        }
        else
        {
            System.err.println("Fail : " + name2);
            assertTrue(false);
        }
        
        ArrayList<Users> userList = Users.select(connector, "person != 0", 10);
        for(Users u : userList)
        {
            System.out.println("User id=" + u.getPerson().getEnte().getID());
            assertTrue(u.getPerson().getEnte().getID() > 0);
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
