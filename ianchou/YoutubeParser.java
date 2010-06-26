package ianchou;

import java.io.*;
import org.apache.commons.httpclient.*;
import org.apache.commons.httpclient.methods.*;
import org.apache.commons.httpclient.params.HttpMethodParams;

public class YoutubeParser{
	private String vid, var_t, URL;
	private String getSegment(String source, String begin, char end){
		int s = source.indexOf(begin);
		if(s<0)
			return "";
		else 
			s = s+begin.length();
		int e = source.indexOf(end, s);
		if(e<0)
			e = source.length();
		return source.substring(s, e);
		
	}
	public String getURL(){
		if(URL != null)
			return URL;
		return null;
	}
	public YoutubeParser(String url){
		vid = getSegment(url,"?v=",'&');
		HttpClient client = new HttpClient();
		GetMethod method = new GetMethod(url);
		try{
			int statusCode = client.executeMethod(method);
			if(statusCode != HttpStatus.SC_OK)
				System.err.println("Method failed: " + method.getStatusLine());
			var_t = getSegment(new String(method.getResponseBody()), "\"t\": \"", '\"');
			URL = "http://www.youtube.com/get_video?video_id="+vid+"&t="+var_t;	
		}catch(HttpException httpexc){
			System.err.println("Fatal protocol violation: " + httpexc.getMessage());
			httpexc.printStackTrace();
		}catch(IOException ioexc){
			System.err.println("Fatal transport error: " + ioexc.getMessage());
			ioexc.printStackTrace();
		}finally{
			method.releaseConnection();		
		}	
	}
}
