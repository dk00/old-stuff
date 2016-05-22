/*
 * MyPokerClient.java
 */

import ca.ualberta.cs.poker.free.client.*;
import ca.ualberta.cs.poker.free.dynamics.Card;
import java.io.*;
import java.net.*;
import java.security.*;
import javax.swing.*;

/**
 * An extension of PokerClient.
 * Actions can be taken with sendFold(), sendCall(), and sendRaise()
 */
public class MyPokerClient extends PokerClient {

	/**
	 * A reproduction of what is happening on the server side.
	 */
	public ClientPokerDynamics state;

	/** 
	 * Creates a new instance of AdvancedPokerClient. Must call connect(), then run() to start process 
	 */
	public MyPokerClient(){
		state = new ClientPokerDynamics();
	}

	/** 
	 * Handles the state change. 
	 * Updates state and calls takeAction()
	 */
	public void handleStateChange() {
		state.setFromMatchStateMessage(currentGameStateString);
		if (state.isOurTurn()) {
			takeAction();
		}
	}

	/**
	 * Overload to take actions.
	 */
	public void takeAction() {
		// FIXME: This is a random player. You should rewrite the code here
		try {

			char a;
			do{
				a=JOptionPane.showInputDialog(currentGameStateString).charAt(0);
			}while(a!='f' && a!='c' && a!='r');
			sendAction(a);
			/*double dart = new SecureRandom().nextDouble();
			if (dart<0.05){
				sendFold();
			} else if (dart<0.55){
				sendCall();
			} else {
				sendRaise();
			}*/
		}catch(IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @param args the command line parameters (IP and port)
	 */
	public static void main(String[] args) throws Exception{
		MyPokerClient rpc = new MyPokerClient();
		System.out.println("Attempting to connect to "+args[0]+" on port "+args[1]+"...");

		rpc.connect(InetAddress.getByName(args[0]),Integer.parseInt(args[1]));
		System.out.println("Successful connection!");
		rpc.run();
	}
}
