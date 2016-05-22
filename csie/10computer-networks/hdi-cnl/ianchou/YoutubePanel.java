package ianchou;

import ianchou.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class YoutubePanel extends JPanel{
	private DownloadPanel downloadPanel;
	private JButton button;
	private JTextField text;
	private JLabel label;
	private JPanel mark;
	public YoutubePanel(DownloadPanel d){
		downloadPanel = d;
		mark = new JPanel(new BorderLayout());
		mark.add(new JLabel(new ImageIcon("./img/youtube.png")), BorderLayout.CENTER);
		label = new JLabel("URL:");
		button = new JButton("get");
		text = new JTextField();
		button.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				String fname = (String)JOptionPane.showInputDialog("file name:");
				if ((fname != null) && (fname.length() > 0))
					downloadPanel.request(new YoutubeParser(text.getText()).getURL(), fname);
			}
		});
		this.setLayout(null);
		mark.setBounds(50,50,700,300);
		this.add(mark);
		label.setBounds(50,400,50,30);
		this.add(label);
		text.setBounds(100,400,500,30);
		this.add(text);
		button.setBounds(600,400,100,30);
		this.add(button);
	}	
}
