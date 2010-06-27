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
	private String[] reqServ;
	private String[] coopServ;
	public Downloader(DownloadPanel d,int t, String host,String url, String fname){
		downloadPanel = d;
		rid = t;
		client = new HttpClient();
		reqServ = new String[]{"http://bsd4.csie.ntu.edu.tw:5555"};
		coopServ = new String[]{"http://bsd2.csie.ntu.edu.tw:5555"};
		//post = new PostMethod(host);
		post = new PostMethod("http://bsd4.csie.ntu.edu.tw:5555");
		String req = "host="+URLEncoder.encode(reqServ[0]);
		for(int i=1;i<reqServ.length;++i)
			req = req +"&" + "host="+URLEncoder.encode(reqServ[i]);
		req = URLEncoder.encode(req);
		String coop = "";
		for(int i=0;i<coopServ.length;++i){
			if(!coop.isEmpty())
				coop = coop + "&";
			coop = coop + "host="+URLEncoder.encode(coopServ[i])+"&cmd=download&req="+req;
		}
		coop = URLEncoder.encode(coop);
    String var = "cmd=download&url="+url+"&path="+fname+"&coop="+coop;
		/*String test = new String("url=http%3A%2F%2Fwww.csie.ntu.edu.tw%2F%7Eb96070%2FNishikaze.wav&path=Nishikaze.wav&coop=host%3Dbsd2.csie.ntu.edu.tw%253A5555%26cmd%3Ddownload%26req%3Dhost%253Dbsd4.csie.ntu.edu.tw%25253A5555&cmd=download");*/
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
						downloadPanel.setSize(rid, size>>10);
					}
					else if(tmp.startsWith("got")){
						int size = new Integer(tmp.substring(3));
						downloadPanel.setGot(rid, size>>10);
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

