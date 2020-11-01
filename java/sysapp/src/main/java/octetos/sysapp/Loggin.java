/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package octetos.sysapp;

import java.io.IOException;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import javax.xml.parsers.ParserConfigurationException;
import octetos.syapp.db.Users;
import org.xml.sax.SAXException;

/**
 *
 * @author azael
 */
public class Loggin extends javax.swing.JInternalFrame {

    private Desktop desktop;
    
    
    /**
     * Creates new form Loggin
     */
    public Loggin(Desktop d) {
        initComponents();
        setTitle("Inicio de Sesion.");
        desktop = d;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        txUser = new javax.swing.JTextField();
        btAccept = new javax.swing.JButton();
        btCancel = new javax.swing.JButton();
        txpwd = new javax.swing.JPasswordField();

        jLabel1.setText("Usuarios : ");

        jLabel2.setText("Contraseña : ");

        btAccept.setText("Aceptar");
        btAccept.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btAcceptActionPerformed(evt);
            }
        });

        btCancel.setText("Cencelar");
        btCancel.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btCancelActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addGap(26, 26, 26)
                        .addComponent(txUser, javax.swing.GroupLayout.PREFERRED_SIZE, 208, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel2)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txpwd)))
                .addContainerGap(86, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(btCancel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btAccept)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(txUser, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(txpwd, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 100, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btAccept)
                    .addComponent(btCancel))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btAcceptActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btAcceptActionPerformed
        Configuration config = null;
        try 
        {
            config = new Configuration();
        } 
        catch (ParserConfigurationException ex) 
        {
            Logger.getLogger(Loggin.class.getName()).log(Level.SEVERE, null, ex);
        } 
        catch (SAXException ex) 
        {
            Logger.getLogger(Loggin.class.getName()).log(Level.SEVERE, null, ex);
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(Loggin.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        octetos.db.mysql.Datconnect dat = new octetos.db.mysql.Datconnect(config.getDataSource());
        
        octetos.db.mysql.Connector connector = new octetos.db.mysql.Connector();
        boolean checkConection = false;
        try
        {
            checkConection = connector.connect(dat);
        }
        catch(java.sql.SQLException e)            
        {
            e.printStackTrace(); 
        }       
        
        
        Users user = new Users();
        boolean check = false;
        try 
        {
            check = user.check(connector, txUser.getText(), txpwd.getText());
        } 
        catch (SQLException ex) 
        {
            Logger.getLogger(Loggin.class.getName()).log(Level.SEVERE, null, ex);
            //JOptionPane.showMessageDialog(this, "Contraseña incorrecta","Usauario/Contraseña incorrectos",JOptionPane.ERROR_MESSAGE);
            return;
        }
        finally
        {
            try
            {
                connector.close();
            }
            catch(java.sql.SQLException e)            
            {
                e.printStackTrace(); 

            }
        }        
        try
        {
            connector.close();
        }
        catch(java.sql.SQLException e)            
        {
            e.printStackTrace(); 
            
        }
        
        
        if(check)
        {
            desktop.enableApplication();
            dispose();
        }
        else
        {
            JOptionPane.showMessageDialog(this, "Contraseña incorrecta","Usauario/Contraseña incorrectos",JOptionPane.ERROR_MESSAGE);
        }
    }//GEN-LAST:event_btAcceptActionPerformed

    private void btCancelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btCancelActionPerformed
        dispose();
    }//GEN-LAST:event_btCancelActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btAccept;
    private javax.swing.JButton btCancel;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JTextField txUser;
    private javax.swing.JPasswordField txpwd;
    // End of variables declaration//GEN-END:variables
}
