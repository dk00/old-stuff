import ianchou.*;

import javax.swing.*;
import java.awt.event.*;
import java.lang.*;
		
public class HDI extends JFrame{
	private ServerPanel serverPanel;
	private DownloadPanel downloadPanel;
	private JTabbedPane jTabbedPane;
	private JMenuBar menuBar;
	private JMenu menu;
	private JMenuItem menuItem;	
	public HDI(){
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(800,600);
		this.setLocationRelativeTo(null);
	
		menuBar = new JMenuBar();
		this.setJMenuBar(menuBar);
		menu = new JMenu("setting");
		menuBar.add(menu);
		menuItem = new JMenuItem("host");
		menuItem.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				String str = JOptionPane.showInputDialog(downloadPanel.hostUrl);
				if(str!=null && !str.isEmpty())
					downloadPanel.hostUrl = str;
			}
		});
		menu.add(menuItem);
		
		jTabbedPane = new JTabbedPane();
		this.add(jTabbedPane);
		serverPanel = new ServerPanel();
		downloadPanel = new DownloadPanel(serverPanel,"http://bsd4.csie.ntu.edu.tw:22222");
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
