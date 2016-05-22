/*
 * AITAPokerClient.java
 */

import ca.ualberta.cs.poker.free.client.*;
import ca.ualberta.cs.poker.free.dynamics.Card;
import java.io.*;
import java.net.*;
import java.security.*;

/**
 * An extension of PokerClient.
 * Actions can be taken with sendFold(), sendCall(), and sendRaise()
 * @author AI TA
 */
public class AITAPokerClient extends PokerClient {

    /**
     * A reproduction of what is happening on the server side.
     */
    public ClientPokerDynamics state;

    /** 
     * Creates a new instance of AdvancedPokerClient. Must call connect(), then run() to start process 
     */
    public AITAPokerClient(){
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
	try {
	    /**
	     * The seat taken by this player.
	     */
	    int seatTaken = state.seatTaken;

	    /** 
	     * Round index incremented when the cards for that round are dealt.
	     * Preflop is 0, Showdown is 4.
	     */
	    int roundIndex = state.roundIndex;

	    if (roundIndex == 0) {
		Card[] hole = state.hole[seatTaken];
		if (hole[0].suit == hole[1].suit) { 
		    sendRaise();
		} else if (hole[0].rank.index >= 9 || hole[1].rank.index >= 9) {
		    sendRaise();
		} else {
		    sendFold();
		} 
	    } else {
		    sendCall();
	    }
	} catch (Exception e) {
		System.out.println(e);
	}
    }

    /**
     * @param args the command line parameters (IP and port)
     */
    public static void main(String[] args) throws Exception{
	AITAPokerClient rpc = new AITAPokerClient();
	System.out.println("Attempting to connect to "+args[0]+" on port "+args[1]+"...");

	rpc.connect(InetAddress.getByName(args[0]),Integer.parseInt(args[1]));
	System.out.println("Successful connection!");
	rpc.run();
    }
}
