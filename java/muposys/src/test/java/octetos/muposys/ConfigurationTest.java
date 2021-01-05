
package octetos.muposys;

import com.mysql.cj.jdbc.MysqlDataSource;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.parsers.ParserConfigurationException;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.xml.sax.SAXException;

/**
 *
 * @author azael
 */
public class ConfigurationTest {
    
    public ConfigurationTest() 
    {
        Configuration config = null;
        try 
        {
            config = new Configuration();
        } 
        catch (ParserConfigurationException | SAXException | IOException ex) 
        {
            Logger.getLogger(ConfigurationTest.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        assertNotEquals(config, null);
        
        MysqlDataSource dat = config.getDataSource();
        assertTrue(dat.getUser().compareTo("muposys") == 0);
        assertTrue(dat.getDatabaseName().compareTo("muposys-0.1-alpha") == 0);
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
     * Test of getDataSource method, of class Configuration.
     */
    @Test
    public void testGetDataSource() {
        
    }

    /**
     * Test of getMySQLDS method, of class Configuration.
     */
    @Test
    public void testGetMySQLDS() {
        
    }
    
}
