import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.*;
//import java.text.*;
public class Download{
	public static void main(String[] args){
		try{
			String s;
			BufferedInputStream input= new BufferedInputStream(
					new URL("http", args[0], 80, args[1]).openStream());
			s = args[1].substring(args[1].lastIndexOf("/")+1);
			BufferedOutputStream output = new BufferedOutputStream(new FileOutputStream(s));
			byte[] data = new byte[1024];
			int count;
			while((count = input.read(data,0,1024))!=-1){
				output.write(data,0,count);
			}
			input.close();
			output.close();
		}catch(Exception e){
			System.out.println(e);
		}
	}
}

