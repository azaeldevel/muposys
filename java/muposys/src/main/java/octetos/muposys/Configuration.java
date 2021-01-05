
package octetos.muposys;


import com.mysql.cj.jdbc.MysqlDataSource;
import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 *
 * @author Azael Reyes
 */
/**
 *
 * @author Azael Reyes
 */
public class Configuration 
{
    private MysqlDataSource datasource;
    private HashMap<String,String> passwords;
    private HashMap<String,String> workspace;
    
    private boolean validateXMLSchema(String xsdPath, String xmlPath)
    {
        try 
        {
            SchemaFactory factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = factory.newSchema(new File(xsdPath));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(new File(xmlPath)));
        }
        catch (IOException e)
        {
            System.out.println("Exception: " + e.getMessage());
            return false;
        }
        catch(SAXException e1)
        {
            System.out.println("SAX Exception: " + e1.getMessage());
            return false;
        }
        
        return true;	
    }
    
    public Configuration() throws ParserConfigurationException, SAXException, IOException 
    {
        loadFile(new java.io.File(".").getCanonicalPath());
    }

    private void loadFile(String file) throws ParserConfigurationException, SAXException, IOException 
    {
        passwords = new HashMap<String,String>();
        passwords.put("956A-981GLP97", "123456");
        passwords.put("956A-981GLP98", "R3sP41Do5");
        passwords.put("956A-9719MOP7", "12345678a");
        passwords.put("956A-9719MOPA", "1234567cd");
        passwords.put("956A-9719GOPA", "Trycer2000");
        passwords.put("956A-971XJOPA", "65094%?¡wrs");
        parseXML(file);
    }
    
    public MysqlDataSource getDataSource()
    {
        return this.datasource;
    }
    public MysqlDataSource getMySQLDS()
    {
        return this.datasource;
    }


    private boolean parseXML(String directory) throws ParserConfigurationException, SAXException, IOException 
    {
        String OS = System.getProperty("os.name").toLowerCase();
        File inputFile;
        File inputFileXSD;
        
        if (OS.contains("windows"))
        {
            inputFile = new File(directory + "\\Configuration.xml");
            inputFileXSD = new File(directory + "\\Configuration.xsd");              
        }
        else if (OS.contains("linux") || OS.contains("Unix"))
        {
            inputFile = new File(directory + "/Configuration.xml");
            inputFileXSD = new File(directory + "/Configuration.xsd");             
        }
        else
        {
            throw new ParserConfigurationException("No Hay soporte para el sistema el SO '" + OS + "'");
        }
                              
        
        boolean isValid = validateXMLSchema(inputFileXSD.getAbsolutePath(),inputFile.getAbsolutePath());         
        if(!isValid)
        {
            throw new ParserConfigurationException("El formto del XML no es valido");
        }
        
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder = null;
        try 
        {
            dBuilder = dbFactory.newDocumentBuilder();
        } 
        catch (ParserConfigurationException ex) 
        {
            Logger.getLogger(Configuration.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
        Document doc = null;
        doc = dBuilder.parse(inputFile);
        doc.getDocumentElement().normalize();
        //System.out.println("Root element :" + doc.getDocumentElement().getNodeName());
        NodeList nList = doc.getElementsByTagName("mysql");
        Node nNode = nList.item(0);
        if (nNode.getNodeType() == Node.ELEMENT_NODE)
        {
            Element eElement = (Element) nNode;
            datasource = new MysqlDataSource();
            datasource.setUser(eElement.getElementsByTagName("user").item(0).getTextContent());
            String pass = this.passwords.get(eElement.getElementsByTagName("code").item(0).getTextContent());
            //System.out.println(">>>> Password:"  + pass);
            datasource.setPassword(pass);
            datasource.setDatabaseName(eElement.getElementsByTagName("database").item(0).getTextContent());
            datasource.setServerName(eElement.getElementsByTagName("host").item(0).getTextContent());            
        }
        
        
        return true;
    }

}
