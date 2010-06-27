import ianchou.*;

import javax.swing.*;
import java.lang.*;

public class HDI extends JFrame{
	private ServerPanel serverPanel;
	private DownloadPanel downloadPanel;
	private JTabbedPane jTabbedPane;
	public HDI(){
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(800,600);
		this.setLocationRelativeTo(null);
	
		jTabbedPane = new JTabbedPane();
		this.add(jTabbedPane);
		serverPanel = new ServerPanel();
		downloadPanel = new DownloadPanel(serverPanel);
		jTabbedPane.add("Download", downloadPanel);
		jTabbedPane.add("Youtube", new YoutubePanel(downloadPanel));
		jTabbedPane.add("Image", new ImagePanel(downloadPanel));
		jTabbedPane.add("Server", serverPanel);
		jTabbedPane.add("Update", new UpdatePanel());
	}
	public static void main(String[] args){
		(new HDI()).setVisible(true);
	}
}
