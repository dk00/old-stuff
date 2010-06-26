import javax.swing.*;
import ianchou.*;

public class HDI extends JFrame{
	private JTabbedPane jTabbedPane;
	public HDI(){
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(600,400);
		this.setLocationRelativeTo(null);
	
		jTabbedPane = new JTabbedPane();
		this.add(jTabbedPane);
		
		jTabbedPane.add("Download", new DownloadPanel());
		jTabbedPane.add("youtube", new YoutubePanel());
	}
	public static void main(String[] args){
		(new HDI()).setVisible(true);
	}
}
