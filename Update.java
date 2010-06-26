import java.net.*;
import java.io.*;
import java.lang.*;
//import java.text.*;
//import java.util.*;

public class Update{
	public static void main(String args[]){
		final int PORT = 80;
		if (args.length<3){
			System.exit(1);
		}
		Socket socket;
		String s, t;
		InputStream IS;
		OutputStream OS;
		BufferedReader BR;
		PrintStream PS;
		try{
			// build client socket
			socket=new Socket(args[0], PORT);
			// build socket stream
			IS=socket.getInputStream();
			OS=socket.getOutputStream();
			// build data stream
			BR = new BufferedReader(new InputStreamReader(IS));
			PS = new PrintStream(OS);
			BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
			
			// do something
			s = "GET " + args[1] + " HTTP/1.0";		PS.println(s);
			s =	"If-Modified-Since: " + args[2];	PS.println(s);
				//Fri, 25 Jun 2010 16:33:36 GMT
			s = "";									PS.println(s);
			s = BR.readLine();
			t = s.substring(9, 12);
			if (t.compareTo("302") == 0){
				//System.out.println("302 Found");
			} else if (t.compareTo("304") == 0){
				//System.out.println("304 Not Modified");
			} else{
				//System.out.println(t);
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
