package ianchou;

import ianchou.*;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
public class UpdatePanel extends JPanel{
	//obj
	private JButton upButton, allButton;
	private JTextField linkField;
	private JLabel label1;
	public JTextArea message;
	public JScrollPane scroll;
	//func
	public void request(String addr, int select){
		Update up = new Update(addr, this, select);
		up.start();
	}
	public UpdatePanel(){
		linkField = new JTextField();
		upButton = new JButton("update");
		allButton = new JButton("update all");
		label1 = new JLabel("URL:");
		message = new JTextArea(15, 1);
		scroll = new JScrollPane(message);
		//function 'n characteristic
		upButton.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				String addr = linkField.getText();
				request(addr, 0);
			}
		});
		allButton.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				String addr = "All links";
				request(addr, 1);
			}
		});
		//JComboBox
		message.setLineWrap(true);
		scroll.createVerticalScrollBar();
		this.setLayout(null);

		label1.setBounds(50,50,50,30);
		this.add(label1);
		linkField.setBounds(100,50,400,30);
		this.add(linkField);
		upButton.setBounds(500,50,100,30);
		this.add(upButton);
		allButton.setBounds(600,50,100,30);
		this.add(allButton);
		scroll.setBounds(50,100,700,400);
		this.add(scroll);
	}	
}
