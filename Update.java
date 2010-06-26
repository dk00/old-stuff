//Usage:	java Update [linkAddr] [lastCheckDate]
//			(ex. java Download w.csie.org/~b96070/hell.jpg Fri,\ 25\ Jun\ 2010\ 16:33:36\ GMT)

import java.net.*;
import java.io.*;
import java.lang.*;
//import java.text.*;
//import java.util.*;

public class Update{
	public static int search(String addr, String time){
		// alloc
		final int PORT = 80;
		int idx;
		Socket socket;
		String s, t;
		InputStream IS;
		OutputStream OS;
		BufferedReader BR;
		PrintStream PS;
		try{
			// parsing
			idx = addr.indexOf("/");
			s = addr.substring(0, idx);
			t = addr.substring(idx);
			// build client socket
			socket = new Socket(s, PORT);
			IS = socket.getInputStream();
			OS = socket.getOutputStream();
			BR = new BufferedReader(new InputStreamReader(IS));
			PS = new PrintStream(OS);
			// do something
			s = "GET " + t + " HTTP/1.0";		PS.println(s);
			s =	"If-Modified-Since: " + time;	PS.println(s);
			s = "";								PS.println(s);
			s = BR.readLine();
			t = s.substring(9, 12);
			// close
			BR.close();
			PS.close(); 
			IS.close(); 
			OS.close(); 
			socket.close();
			// return http response #
			return Integer.valueOf(t).intValue();
		}
		catch(Exception e){
			System.out.println("Error:"+e);
		}
		return -1;
	}

	public static void main(String args[]){
		//int i = Update.search("w.csie.org/~b96070/hell.jpg", "Fri, 25 Jun 2010 16:33:36 GMT");
		int i = Update.search(args[0], args[1]);
		System.out.println(i);
	}
}
