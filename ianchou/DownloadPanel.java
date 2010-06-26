package ianchou;

import ianchou.*;
import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
class ButtonRenderer extends JButton implements TableCellRenderer {
  public ButtonRenderer() {
    setOpaque(true);
  }
  public Component getTableCellRendererComponent(JTable table, Object value,
      boolean isSelected, boolean hasFocus, int row, int column) {
    if (isSelected) {
      setForeground(table.getSelectionForeground());
      setBackground(table.getSelectionBackground());
    } else {
      setForeground(table.getForeground());
      setBackground(UIManager.getColor("Button.background"));
    }
    setText((value == null) ? "" : value.toString());
    return this;
  }
}
class ButtonEditor extends DefaultCellEditor {
  protected JButton button;
  private String label;
  private boolean isPushed;
  public ButtonEditor(JCheckBox checkBox) {
    super(checkBox);
    button = new JButton();
    button.setOpaque(true);
    button.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        fireEditingStopped();
      }
    });
  }
  public Component getTableCellEditorComponent(JTable table, Object value,
      boolean isSelected, int row, int column) {
    if (isSelected) {
      button.setForeground(table.getSelectionForeground());
      button.setBackground(table.getSelectionBackground());
    } else {
      button.setForeground(table.getForeground());
      button.setBackground(table.getBackground());
    }
    label = (value == null) ? "" : value.toString();
    button.setText(label);
    isPushed = true;
    return button;
  }

  public Object getCellEditorValue() {
    if (isPushed) {
      JOptionPane.showMessageDialog(button, label + ": Ouch!");
      // System.out.println(label + ": Ouch!");
    }
    isPushed = false;
    return new String(label);
  }

  public boolean stopCellEditing() {
    isPushed = false;
    return super.stopCellEditing();
  }

  protected void fireEditingStopped() {
    super.fireEditingStopped();
  }
}

public class DownloadPanel extends JPanel{
	private DefaultTableModel model;
	private JButton jButton;
	private JTable jTable;
	private JTextField urlField, fnameField;
	private JScrollPane scrollPane;
	private int pid;
	public DownloadPanel(){
		urlField = new JTextField();
		fnameField = new JTextField();
		jButton = new JButton("download!");
		model = new DefaultTableModel();
		jTable = new JTable(model); 	
		model.addColumn("ID"); model.addColumn("URL"); model.addColumn("status");
		model.addColumn("delete");
		jTable.getColumn("delete").setCellRenderer(new ButtonRenderer());
		jTable.getColumn("delete").setCellEditor(new ButtonEditor(new JCheckBox()));
		pid = 1;
		scrollPane = new JScrollPane(jTable);
		TableModel tableModel = jTable.getModel();
		jButton.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				new Downloader("http://127.0.0.1:11111",urlField.getText(),fnameField.getText()).start();
				model.addRow(new Object[]{pid++,"","",""});
			}
		});
		this.setLayout(new GridBagLayout());
		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.NONE;
		c.weightx = 0.5;
		c.weighty = 0.2;
		c.gridx = 0;
		c.gridy = 0;
		this.add(new Label("URL:"),c);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 1;
		this.add(urlField, c);
		c.fill = GridBagConstraints.NONE;
		c.gridx = 2;
		this.add(new Label("FileName:"),c);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 3;
		this.add(fnameField, c);
		c.fill = GridBagConstraints.NONE;
		c.gridx = 4;
		this.add(jButton, c);
		c.fill = GridBagConstraints.BOTH;
		c.weighty = 0.8;
		c.gridx = 0;
		c.gridy = 1;
		c.gridwidth = 5;
		this.add(scrollPane, c);
	}	
}
