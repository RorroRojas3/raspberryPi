/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package client;
import java.net.*;
import java.io.*;


/**
 *
 * @author rorro
 */
public class Client 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException 
    {
        // Creates client socket
        Socket client = new Socket("localhost",50505);
        
        // Creates variable which will store data to send to Server
        InputStream clientInput = client.getInputStream();
        
        // Creates variable which will store data received from Server
        DataInputStream serverOutput = new DataInputStream(clientInput);
        
        // Reads the data sent from the Server and stores on variable
        String serverData = new String (serverOutput.readLine());
        
        // Prints data received from Server
        System.out.println(serverData);
        
        
        // Closes the input from Server
        serverOutput.close();
        // Closes the input from Client
        clientInput.close();
        // Closes Client Socket
        client.close();

    }
    
}
