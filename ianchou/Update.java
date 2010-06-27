package ianchou;

import java.net.*;
import java.io.*;
import java.lang.*;
import java.text.*;
import java.util.*;

public class Update extends Thread{
	private static Object syncObject = new Object();  
	private int select;
	final int SINGLE = 0;
	final int MULTI = 1;
	private String addr;
	private UpdatePanel panel;
	private String getTime(){
		SimpleDateFormat df = new SimpleDateFormat(
			"EEE, d MMM yyyy HH:mm:ss ", new Locale("en"));
		return df.format(new Date()) + "GMT";
	}
	private void download(String addr){
		try{
			//init
			String s, t;
			byte[] data = new byte[1024];
			int count, idx;
			//alloc
			idx = addr.indexOf("/");
			if (idx == -1){
				s = addr;
				t = "/index.html";
			} else {
				s = addr.substring(0, idx);
				t = addr.substring(idx);
			}
			System.out.println(s + " _ " + t);
			BufferedInputStream input = new BufferedInputStream(
					new URL("http", s, 80, t).openStream());
			if (idx == -1){
				s = "index.html";
			} else {
				s = t.substring(t.lastIndexOf("/")+1);
			}
			BufferedOutputStream output = new BufferedOutputStream(
					new FileOutputStream(s));
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
	public int search() throws IOException{
		System.out.println(this.addr);
		int check = 0;
		String s, t;
		BufferedReader in = new BufferedReader(
								new FileReader("ianchou/mydata"));
		BufferedWriter out = new BufferedWriter(
								new FileWriter("ianchou/mydata.tmp"));
		while ( (s = in.readLine()) != null ) {
			if ( s.compareTo(this.addr) == 0 || select == MULTI){
				panel.message.append(s + " is found in the list.\n");
				check = 1;
				t = in.readLine();
				int res = getResponse(s, t);
				handleResponse(s, res);
				//output
				if (res == 302 || res == 304 || res == 200){
					out.write(s);	out.newLine();
					t = this.getTime();
					out.write(t);	out.newLine();
				}
				continue;
			}
			//output
			out.write(s);	out.newLine();
		}
		if (check == 0 && select == SINGLE){
			panel.message.append(this.addr + " is not in the list.\n");
			t = this.getTime();
			int res = getResponse(this.addr, t);
			handleResponse(this.addr, res);
			//output
			if (res == 302 || res == 304 || res == 200){
				out.write(this.addr);	out.newLine();
				out.write(t);		out.newLine();
			}
		}
		in.close();		out.close();
		panel.message.append("Update done.\n");
		return 0;
	}
	private void handleResponse(String s, int response){
		switch (response){
			case 302:	
				panel.message.append(s + " need not to update.\n");
				break;	//found
			case 304://not modified
			case 200://ok
				panel.message.append(s + " is available.\n");
				this.download(s);
				break;
			case 404:
				panel.message.append(s + " is broken.\n");
				break;	//not found
			default:
				panel.message.append(s + " is in case " + response + ".\n");
				panel.message.append("We will not handle this case.\n");
				break;
		}
	}
	private int getResponse(String addr, String time){
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
			if (idx == -1){
				s = addr;
				t = "/index.html";
			} else {
				s = addr.substring(0, idx);
				t = addr.substring(idx);
			}
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
	public Update(String addr, UpdatePanel panel, int select){
		this.addr = addr;
		this.panel = panel;
		this.select = select;
	}
	public void run(){
		try{
			panel.message.append(addr + " is(are) waiting for update.\n");
			synchronized(syncObject){
				this.search();
				Process p = Runtime.getRuntime().exec("mv ianchou/mydata.tmp ianchou/mydata");
			}
		} catch (IOException e){
			System.out.println("Error:"+e);
		}
	}
}
