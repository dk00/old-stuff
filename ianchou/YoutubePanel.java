package ianchou;

import ianchou.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class YoutubePanel extends JPanel{
	private JButton button;
	private JTextField text;
	private JTextArea msg;
	private JLabel label;
	private JPanel mark;
	public YoutubePanel(){
		mark = new JPanel(new BorderLayout());
		mark.add(new JLabel(new ImageIcon("./img/youtube.jpeg")), BorderLayout.CENTER);
		label = new JLabel("URL:");
		button = new JButton("get!!!");
		text = new JTextField();
		msg = new JTextArea("wait");	
		button.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				msg.setText(new YoutubeParser(text.getText()).getURL());
			}
		});
		msg.setEditable(false);
		msg.setBackground(Color.GRAY);
		this.setBackground(Color.WHITE);
		this.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		c.weighty = 0.5;
		c.gridx=0;
		c.gridy=0;
		c.gridwidth=10;
		c.fill = GridBagConstraints.BOTH;
		this.add(mark, c);
		c.weighty = 0.2;
		c.weightx = 0.1;
		c.gridx=0;
		c.gridy=1;
		c.gridwidth=1;
		c.gridheight=1;
		this.add(label, c);
		c.weightx = 0.8;
		c.gridx=1;
		c.gridwidth=7;
		c.fill = GridBagConstraints.HORIZONTAL;
		this.add(text, c);
		c.weightx = 0.1;
		c.gridx=8;
		c.gridy=1;
		c.gridwidth=1;
		c.fill = GridBagConstraints.NONE;
		this.add(button, c);
		c.weighty = 0.1;
		c.gridx=0;
		c.gridy=2;
		c.gridwidth=10;
		c.fill = GridBagConstraints.HORIZONTAL;
		c.anchor = GridBagConstraints.SOUTH;
		this.add(msg,c);
	}	
}
