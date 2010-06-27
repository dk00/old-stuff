package ianchou;

import ianchou.*;
import javax.swing.*;
import javax.swing.table.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
class MyTableModel extends DefaultTableModel{
	public MyTableModel(){
		super();
	}
	public boolean isCellEditable(int r,int c){
		if(c==4)
			return true;
		else
			return false;
	}
}
public class ServerPanel extends JPanel{
	private JButton button;
	private JTextField urlText;
	private JLabel urlLabel;
	private JTextField portText;
	private JLabel portLabel;
	private JTextField idText;
	private JLabel idLabel;
	private JPasswordField pw;
	private JLabel pwLabel;
	private ArrayList<char[]> password;
	private MyTableModel model;
	private JTable table;
	private JScrollPane scrollPane;
	public ServerPanel(){
		password = new ArrayList<char[]>();
		urlLabel = new JLabel("URL:");
		portLabel = new JLabel("port:");
		idLabel = new JLabel("ID:");
		pwLabel = new JLabel("PW:");
		button = new JButton("add");
		urlText = new JTextField();
		portText = new JTextField();
		idText = new JTextField();
		pw = new JPasswordField();
		model = new MyTableModel();
		table = new JTable(model);
		table.setAutoCreateRowSorter(true);
		model.addColumn("NO."); model.addColumn("URL"); 
		model.addColumn("port"); model.addColumn("ID"); 
		model.addColumn("select");
		table.getColumnModel().getColumn(4).setCellEditor(new DefaultCellEditor(new JCheckBox()));	
		button.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
					password.add(pw.getPassword());
					model.addRow(new Object[]{password.size(),
						urlText.getText(),
						portText.getText(),
						idText.getText(),
						new Boolean(false)});
			}
		});
		scrollPane = new JScrollPane(table);
		this.setLayout(null);
		urlLabel.setBounds(50,50,50,30);
		this.add(urlLabel);
		urlText.setBounds(100,50,450,30);
		this.add(urlText);
		portLabel.setBounds(550,50,50,30);
		this.add(portLabel);
		portText.setBounds(600,50,100,30);
		this.add(portText);
		
		idLabel.setBounds(50,100,50,30);
		this.add(idLabel);
		idText.setBounds(100,100,200,30);
		this.add(idText);
		pwLabel.setBounds(350,100,50,30);
		this.add(pwLabel);
		pw.setBounds(400,100,200,30);
		this.add(pw);
		button.setBounds(600,100,100,30);
		this.add(button);
		scrollPane.setBounds(50,150,700,350);
		this.add(scrollPane);
	}	
}
