//Usage:	java Download [linkAddr]
//			(ex. java Download w.csie.org/~b96070/hell.jpg)

import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.*;
//import java.text.*;
public class Download{
	public static void main(String[] args){
		try{
			//init
			String s, t;
			byte[] data = new byte[1024];
			int count, idx;
			//alloc
			idx = args[0].indexOf("/");
			s = args[0].substring(0, idx);
			t = args[0].substring(idx);
			BufferedInputStream input = new BufferedInputStream(
					new URL("http", s, 80, t).openStream());
			s = t.substring(t.lastIndexOf("/")+1);
			BufferedOutputStream output = new BufferedOutputStream(new FileOutputStream(s));
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
}

