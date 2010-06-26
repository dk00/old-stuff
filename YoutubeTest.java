import ianchou.*;
import java.util.*;
import java.io.*;
import java.net.*;

public class YoutubeTest{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		System.out.println("please input youtube URL:");
		while(in.hasNext()){
			try{
				BufferedInputStream input= new BufferedInputStream(new URL(new YoutubeParser(in.nextLine()).getURL()).openStream());
				BufferedOutputStream output = new BufferedOutputStream(new FileOutputStream("test.flv"));
				byte[] data = new byte[1024];
				int count;
				while((count = input.read(data,0,1024))!=-1){
					output.write(data,0,count);
				}
				System.out.println("done");
				input.close();
				output.close();
			}catch(Exception e){
				System.out.println(e);
			}
		}
	}
}
