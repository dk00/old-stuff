package ianchou;

import org.apache.commons.httpclient.*;
import org.apache.commons.httpclient.methods.*;
import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.*;
public class Downloader extends Thread{
	private ServerPanel serverPanel;
	private DownloadPanel downloadPanel;
	private HttpClient client;
	private PostMethod post;
	private int rid;
	private String[] reqServ;
	private String[] coopServ;
	public Downloader(ServerPanel sp,DownloadPanel dp,int t, String host,String url, String fname){
		serverPanel = sp;
		downloadPanel = dp;
		rid = t;
		client = new HttpClient();
		reqServ = new String[]{host};
		coopServ = sp.getCoopServ();
		post = new PostMethod(host);
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
    String var = "cmd=download&url="+URLEncoder.encode(url)+"&path="+fname+"&coop="+coop;
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

