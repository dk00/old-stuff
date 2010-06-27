import java.net.*;
import java.io.*;
import java.lang.*;
import java.text.*;
import java.util.*;

public class Update{
	private static String getTime(){
		SimpleDateFormat df = new SimpleDateFormat(
			"EEE, d MMM yyyy HH:mm:ss ", new Locale("en"));
		return df.format(new Date()) + "GMT";
	}
	private static void download(String arg){
		try{
			//init
			String s, t;
			byte[] data = new byte[1024];
			int count, idx;
			//alloc
			idx = arg.indexOf("/");
			s = arg.substring(0, idx);
			t = arg.substring(idx);
			BufferedInputStream input = new BufferedInputStream(
					new URL("http", s, 80, t).openStream());
			s = t.substring(t.lastIndexOf("/")+1);
			BufferedOutputStream output = new BufferedOutputStream(
					new FileOutputStream("tmp/" + s));
			//r/w
			while((count = input.read(data,0,1024))!=-1){
				output.write(data,0,count);
			}
			//close
			input.close();
			output.close();
		}catch(Exception e){
			System.out.println(e);
		}
	}
	public static int search(String addr) throws IOException{
		int check = 0;
		String s, t;
		BufferedReader in = new BufferedReader(
								new FileReader("mydata"));
		BufferedWriter out = new BufferedWriter(
								new FileWriter("tmp/mydata"));
		while ( (s = in.readLine()) != null ) {
			if ( s.compareTo(addr) == 0 ){
				check = 1;
				t = in.readLine();
				switch (update(addr, t)){
					case 302:	break;	//found
					case 304://not modified
					case 200://ok
						Update.download(addr);
						break;
					case 404:	break;	//not found
					default:	break;
				}
				out.write(s);	out.newLine();
				t = Update.getTime();
				out.write(t);	out.newLine();
				continue;
			}
			out.write(s);	out.newLine();
		}
		if (check == 0){
			t = Update.getTime();
			switch (update(addr, t)){
				case 302:	break;	//found
				case 304://not modified
				case 200://ok
							Update.download(addr);
							break;
				case 404:	break;	//not found
				default:	break;
			}
			out.write(addr);	out.newLine();
			out.write(t);		out.newLine();
		}
		in.close();		out.close();
		return 0;
	}
	private static int update(String addr, String time){
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
	public Update(String s) throws IOException{
		Update.search(s);
	}
	public static void main(String args[]) throws IOException{
		Update.search(args[0]);
	}
}
