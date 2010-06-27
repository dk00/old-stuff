package ianchou;

import org.apache.commons.httpclient.*;
import org.apache.commons.httpclient.methods.*;
import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.*;
public class Downloader extends Thread{
	private DownloadPanel downloadPanel;
	private HttpClient client;
	private PostMethod post;
	private int rid;
	public Downloader(DownloadPanel d,int t, String host,String url, String fname){
		downloadPanel = d;
		rid = t;
		client = new HttpClient();
		post = new PostMethod(host);
		NameValuePair[] var = {
			new NameValuePair("cmd", "download"),
			new NameValuePair("url", url),
			new NameValuePair("path", fname)
		};
		System.out.println(url+" "+fname);  //debug
		post.setRequestBody(var);
	}
	public void run(){
		try{
			if(client.executeMethod(post) != HttpStatus.SC_OK){
				System.err.println("Method filed: " + post.getStatusLine());	
				downloadPanel.setStatus(rid,"failed!");
			}
			InputStream in = post.getResponseBodyAsStream();
			StringBuffer str = new StringBuffer();
			int c;
			while((c=in.read())!=-1){
				if(c=='\n'){
					String tmp = str.toString();
					if(tmp.startsWith("file size:")){
						int size = new Integer(tmp.substring(11));
						downloadPanel.setSize(rid, size/1000);
					}
					else
						downloadPanel.setStatus(rid, tmp);
					str = new StringBuffer();
				}
				else
					str.append((char)c);
					
			}
		}catch(Exception e){
			System.out.println(e);
			downloadPanel.setStatus(rid,"failed");
		}finally{
			post.releaseConnection();
		}
	}
}

