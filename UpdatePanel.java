import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
public class UpdatePanel extends JPanel{
	private JButton upButton, allButton;
	private JTextField linkField;
	public UpdatePanel(){
		linkField = new JTextField();
		upButton = new JButton("update");
		allButton = new JButton("update all");
		
		upButton.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				String s = linkField.getText();
				try {
					new Update(s);
				} catch(IOException ex) {
					System.out.println("Error:" + ex);
				}
			}
		});
		JLabel label1 = new JLabel("link:");

		this.setLayout(null);	//??????????

		label1.setBounds(50,50,50,30);
		this.add(label1);
		linkField.setBounds(100,50,250,30);
		this.add(linkField);
		upButton.setBounds(100,650,100,30);
		this.add(upButton);
		allButton.setBounds(200,650,100,30);
		this.add(allButton);
	}	
}
