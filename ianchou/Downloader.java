package ianchou;

import org.apache.commons.httpclient.*;
import org.apache.commons.httpclient.methods.*;
import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.*;
public class Downloader extends Thread{
	private HttpClient client;
	private PostMethod post;
	public Downloader(String host,String url, String fname){
		client = new HttpClient();
		post = new PostMethod(host);
		NameValuePair[] var = {
			new NameValuePair("cmd", "download"),
			new NameValuePair("url", url),
			new NameValuePair("path", fname)
		};
		post.setRequestBody(var);
	}
	public void run(){
		try{
			if(client.executeMethod(post) != HttpStatus.SC_OK)
				System.err.println("Method filed: " + post.getStatusLine());
		}catch(Exception e){
			System.out.println(e);
		}finally{
			post.releaseConnection();
		}
	}
}

