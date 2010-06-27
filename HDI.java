import ianchou.*;

import javax.swing.*;
import java.lang.*;

public class HDI extends JFrame{
	private ServerPanel serverPanel;
	private DownloadPanel downloadPanel;
	private JTabbedPane jTabbedPane;
	private Process serverProcess;
	public HDI(){
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(800,600);
		this.setLocationRelativeTo(null);
	
		jTabbedPane = new JTabbedPane();
		this.add(jTabbedPane);
		try{		
			serverProcess = Runtime.getRuntime().exec("./serv.py 11111");
		}catch(Exception e){
			System.err.println("server failed: " + e);
		}
		serverPanel = new ServerPanel();
		downloadPanel = new DownloadPanel(serverPanel);
		jTabbedPane.add("Download", downloadPanel);
		jTabbedPane.add("Youtube", new YoutubePanel(downloadPanel));
		jTabbedPane.add("Image", new ImagePanel(downloadPanel));
		jTabbedPane.add("Server", new ServerPanel());
		jTabbedPane.add("Update", new UpdatePanel());
	}
	public void finalize(){
		serverProcess.destroy();
	}
	public static void main(String[] args){
		(new HDI()).setVisible(true);
	}
}
