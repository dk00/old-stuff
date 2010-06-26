import java.net.*;
import java.io.*;
import java.lang.*;
//import java.text.*;
//import java.util.*;

public class Update{
	public static void main(String args[]){
		final int PORT = 80;
		if (args.length<2){
			System.exit(1);
		}
		Socket socket;
		String s, t;
		InputStream IS;
		OutputStream OS;
		BufferedReader BR;
		PrintStream PS;
			//Date date = new Date();
			//Locale locale = new Locale("en");
			//DateFormat DF = new SimpleDateFormat("EEE, d MMM yyyy HH:mm:ss", locale);
		try{
			// build client socket
			socket=new Socket(args[0], PORT);
			// notify user
			System.out.println("client ok");
			System.out.println("************************************************");
			System.out.println("");
			// build socket stream
			IS=socket.getInputStream();
			OS=socket.getOutputStream();
			// build data stream
			BR = new BufferedReader(new InputStreamReader(IS));
			PS = new PrintStream(OS);
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			// do something
			s = "GET " + args[1] + " HTTP/1.0";
			PS.println(s);
				//s =	"If-Modified-Since: " + DF.format(date) + " GMT";	//current time
			s =	"If-Modified-Since: Fri, 25 Jun 2010 16:33:36 GMT";
			PS.println(s);
			s = "";
			PS.println(s);
			s = BR.readLine();
			t = s.substring(9, 12);
			if (t.compareTo("302") == 0){
				System.out.println("302 Found");
			} else if (t.compareTo("304") == 0){
				System.out.println("304 Not Modified");
			} else{
				System.out.println(t);
			}

			// close
			BR.close();
			PS.close(); 
			IS.close(); 
			OS.close(); 
			socket.close();
		}
		catch(Exception e){
			System.out.println("Error:"+e);
		}
	}
}
