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
		return false;
	}	
}
public class DownloadPanel extends JPanel{
	private ServerPanel serverPanel;
	private DefaultTableModel model;
	private JButton jButton;
	private JTable jTable;
	private JTextField urlField, fnameField;
	private JScrollPane scrollPane;
	public String hostUrl;
	public void request(String url, String fname){
		int rid = jTable.getRowCount();
		model.addRow(new Object[]{url,fname,0,0,"downloading"});
		new Downloader(serverPanel,this,rid,hostUrl,url,fname).start();
	}
	public void setStatus(int rid, String str){
		jTable.setValueAt(str,rid,4);
	}
	public void setSize(int rid, int size){
		jTable.setValueAt(size,rid,2);
	}
	public void setGot(int rid,int size){
		int total = (Integer)jTable.getValueAt(rid,2);
		int now = (Integer)jTable.getValueAt(rid,3) + size;
		if(now > total)
			jTable.setValueAt(total,rid,3);
		else
			jTable.setValueAt(now,rid,3);
	}
	public DownloadPanel(ServerPanel sp, String hu){
		serverPanel = sp;
		hostUrl = hu;
		urlField = new JTextField();
		fnameField = new JTextField();
		jButton = new JButton("get");
		model = new DefaultTableModel();
		jTable = new JTable(model);
		jTable.setAutoCreateRowSorter(true);
		model.addColumn("URL"); model.addColumn("FileName"); 
		model.addColumn("Size(kb)"); model.addColumn("Got(kb)");
		model.addColumn("Status");
		scrollPane = new JScrollPane(jTable);
		TableModel tableModel = jTable.getModel();
		jButton.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				String s = urlField.getText(), f = fnameField.getText();
				if(f.isEmpty())
					request(s, s.substring(s.lastIndexOf("/")+1));
				else
					request(s, f);
			}
		});
		JLabel label1 = new JLabel("URL:"), label2 = new JLabel("FileName:");
		this.setLayout(null);
		label1.setBounds(50,50,50,30);
		this.add(label1);
		urlField.setBounds(100,50,250,30);
		this.add(urlField);
		label2.setBounds(370,50,80,30);
		this.add(label2);
		fnameField.setBounds(450,50,200,30);
		this.add(fnameField);
		jButton.setBounds(650,50,100,30);
		this.add(jButton);
		scrollPane.setBounds(50,100,700,400);
		this.add(scrollPane);
	}	
}
