package ianchou;

import org.htmlparser.*;
import org.htmlparser.tags.*;
import org.htmlparser.util.*;
import org.htmlparser.filters.*;
import java.io.*;
import java.util.*;
import java.net.*;

public class ImageParser{
	private ArrayList<ImageInfo> URLs;
	public	ImageInfo[] getURLs(){
		return URLs.toArray(new ImageInfo[URLs.size()]);
	}
	public ImageParser(String url){
		URLs = new ArrayList<ImageInfo>();
		try{
			Parser parser = new Parser(url);
			//parser.setEncoding("utf-8");
				/*NodeFilter frameFilter = new NodeFilter(){
					public boolean accept(Node node){
						if(node.getText().startsWith("frame src="))
							return true;
						else
							return false;
					}
				};
				OrFilter orFilter = new OrFilter(new NodeClassFilter(LinkTag.class), new NodeClassFilter(ImageTag.class));
				OrFilter linkFilter = new OrFilter(orFilter, frameFilter);*/
			NodeList list = parser.extractAllNodesThatMatch(new NodeClassFilter(ImageTag.class));
			for(int i=0; i<list.size(); ++i){
				Node tag = list.elementAt(i);
				if(tag instanceof ImageTag){
					ImageTag image = (ImageTag)list.elementAt(i);
					URLs.add(new ImageInfo(image.getImageURL(), image.getAttribute("title"), new Integer(image.getAttribute("width")),new Integer(image.getAttribute("height"))));
				}
			}
		}catch (ParserException e){
			e.printStackTrace();
		}
	}
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in);
		while(scanner.hasNextLine()){
			new ImageParser(scanner.nextLine());
		}
	}
}
