package hw05.clchen;

import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Node;
import org.w3c.dom.Document;
import org.w3c.dom.Text;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.NodeList;

public class DumpXml {

    public static void main(String[] args) throws Exception {
	DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	DocumentBuilder builder = factory.newDocumentBuilder();
	Document doc = builder.parse(new File(args[0]));

	System.out.println(factory);
	System.out.println(builder);
	System.out.println();
	
	printNode(doc, "");
    }
    
    static void printNode(Node node, String serialNumber) {
	System.out.print(serialNumber + node.getClass().getSimpleName() + ":" + node);
	if (node.hasAttributes()) {
	    NamedNodeMap nnm = node.getAttributes();
	    for (int i = 0; i < nnm.getLength(); i++) {
		System.out.print(" " + nnm.item(i));
	    }
	}
	System.out.println();
	NodeList nl = node.getChildNodes();
	for (int i = 0, j = 0; i < nl.getLength(); i++) {
	    Node n = nl.item(i);
	    if (n instanceof Text) {
		if (((Text)n).getData().trim().length() == 0) continue;
	    }
	    printNode(n, serialNumber + (++j) + ".");
	}
    }
}
