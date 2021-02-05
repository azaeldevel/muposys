
package octetos.muposys.db;

import java.sql.SQLException;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author azael
 */
public class Test 
{
    public static void main(String args[]) 
    {
        Test test = new Test();
        try 
        {
            test.suid();
        } 
        catch (SQLException ex) 
        {
            Logger.getLogger(Test.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void suid() throws SQLException
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
        }
        
        Random rand = new Random(); 
        int r = rand.nextInt(100000);
        
        String userstr,name,userstr2,name2,userstr3,name3,projectName,rqname1,rqname2,rqname3;
        
        userstr = "user-";
        userstr += r;
        name = "name-";
        name += r;
        Users user = new Users();
        if(user.insert(connector,userstr,name))
        {
            System.out.println("insert : " + name);
        }
        else
        {
            System.err.println("Fail : " + name);
        }
        
        Date date = new Date();
        Timestamp ts = new Timestamp(date.getTime());  
        SimpleDateFormat formatter = new SimpleDateFormat("yyyyMMddHHmmss");  
        String md5 = formatter.format(ts);
        //System.out.println(md5);
        if(user.getPerson().getEnte().upMd5sum(connector,md5))
        {
            System.out.println("update id=" + user.getPerson().getEnte().getID() + ", md5=" + md5);
        }
        
        r = rand.nextInt(100000);
        userstr2 = "user-";
        userstr2 += r;
        name2 = "name-";
        name2 += r;
        Users user2 = new Users();
        if(user2.insert(connector,userstr2,name2))
        {
            //System.out.println("insert : " + name2);
        }
        else
        {
            System.err.println("Fail : " + name2);
        }
        
        r = rand.nextInt(100000);
        userstr3 = "user-";
        userstr3 += r;
        name3 = "name-";
        name3 += r;
        Users user3 = new Users();        
        if(user3.insert(connector,userstr3,name3))
        {
            System.out.println("insert : " + name2);
        }
        else
        {
            System.err.println("Fail : " + name3);
        }
        if(user3.remove(connector))
        {
            System.out.println("remove : " + name3);
        }
        else
        {
            System.err.println("Fail : " + name3);
        }        
        ArrayList<Users> userList = Users.select(connector, "person != 0", 10, 'D');
        for(Users u : userList)
        {
            System.out.println("User id=" + u.getPerson().getEnte().getID());
        }
        
        
        
        
        r = rand.nextInt(100000);
        projectName = "proj-";
        projectName += r;
        SoftwareProjects proj = new SoftwareProjects();        
        if(proj.insert(connector,projectName))
        {
            System.out.println("insert : " + projectName);
        }
        else
        {
            System.err.println("Fail : " + projectName);
        }
        int lastRQNumber = 1;
        String where = "project = ";
        where += proj.getEnteValue();
        ArrayList<SoftwareRQs> rqsList = SoftwareRQs.select(connector,where,3,'D');
        if(rqsList.size() > 0)
        {
            SoftwareRQs rqlast = rqsList.get(0);
            if(rqlast.downNumber(connector))
            {
                lastRQNumber = rqlast.getNumber();
            }
            else
            {
                System.err.println("Fallo la descarga de lastRQNumber en '" + projectName + "");
            }
        }        
        r = rand.nextInt(100000);
        rqname1 = "rq-";
        rqname1 += r;
        SoftwareRQs rq1 = new SoftwareRQs();        
        if(rq1.insert(connector,proj,lastRQNumber++,rqname1,1))
        {
            System.out.println("insert : " + rqname1);
        }
        else
        {
            System.err.println("Fail : " + rqname1);
        }
        r = rand.nextInt(100000);
        rqname2 = "rq-";
        rqname2 += r;
        SoftwareRQs rq2 = new SoftwareRQs();        
        if(rq2.insert(connector,proj,lastRQNumber++,rqname2,1))
        {
            System.out.println("insert : " + rqname2);
        }
        else
        {
            System.err.println("Fail : " + rqname2);
        }
        r = rand.nextInt(100000);
        rqname3 = "rq-";
        rqname3 += r;
        SoftwareRQs rq3 = new SoftwareRQs();        
        if(rq3.insert(connector,proj,lastRQNumber++,rqname3,1))
        {
            System.out.println("insert : " + rqname3);
        }
        else
        {
            System.err.println("Fail : " + rqname3);
        }
    }
}
