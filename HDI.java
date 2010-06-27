import javax.swing.*;
import ianchou.*;

public class HDI extends JFrame{
	private DownloadPanel downloadPanel;
	private JTabbedPane jTabbedPane;
	public HDI(){
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(800,600);
		this.setLocationRelativeTo(null);
	
		jTabbedPane = new JTabbedPane();
		this.add(jTabbedPane);
		try{		
			Runtime.getRuntime().exec("./serv.py 11111");
		}catch(Exception e){
			System.err.println("server failed: " + e);
		}
		downloadPanel = new DownloadPanel();
		jTabbedPane.add("Download", downloadPanel);
		jTabbedPane.add("Youtube", new YoutubePanel(downloadPanel));
		jTabbedPane.add("Image", new ImagePanel(downloadPanel));
	}
	public static void main(String[] args){
		(new HDI()).setVisible(true);
	}
}
