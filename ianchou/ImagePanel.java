package ianchou;

import ianchou.*;
import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
class MyTableModel extends DefaultTableModel{
	public MyTableModel(){
		super();
	}
	public boolean isCellEditable(int r,int c){
		if(c==2)
			return true;
		else
			return false;
	}
}
public class ImagePanel extends JPanel{
	private DownloadPanel downloadPanel;
	private JButton button1;
	private JButton button2;
	private JTextField text;
	private JLabel label;
	private MyTableModel model;
	private JTable table;
	private JScrollPane scrollPane;
	public ImagePanel(DownloadPanel d){
		downloadPanel = d;
		label = new JLabel("URL:");
		button1 = new JButton("圖片");
		button2 = new JButton("下載");
		text = new JTextField();
		model = new MyTableModel();
		table = new JTable(model);
		model.addColumn("URL"); model.addColumn("info"); model.addColumn("select");	
		table.getColumnModel().getColumn(2).setCellEditor(new DefaultCellEditor(new JCheckBox()));
		
		button1.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				String[] urls = new ImageParser(text.getText()).getURLs();
				for(int i=0;i<urls.length;++i)
					model.addRow(new Object[]{urls[i],"orz",new Boolean(false)});
			}
		});
		button2.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				for(int i=0;i<table.getRowCount();++i)
					if((Boolean)table.getValueAt(i,2)){
						String tmp = (String)table.getValueAt(i,0);
						downloadPanel.request(tmp,tmp.substring(tmp.lastIndexOf("/")+1));				
					}
			}
		});
		scrollPane = new JScrollPane(table);
		this.setLayout(null);
		label.setBounds(50,50,50,30);
		this.add(label);
		text.setBounds(100,50,400,30);
		this.add(text);
		button1.setBounds(500,50,100,30);
		this.add(button1);
		button2.setBounds(600,50,100,30);
		this.add(button2);
		scrollPane.setBounds(50,100,700,400);
		this.add(scrollPane);
	}	
}
