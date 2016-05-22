package hw08.b96902120;
import java.awt.*;
import javax.swing.*;
import com.sun.tools.javac.Main;
public class JavacTest{
    public static void main(String arg[])throws Exception{
        if(arg.length>0)
        {
            Main.main(arg);
            return;
        }
        JFileChooser fc=new JFileChooser();
        if(fc.showOpenDialog(new Container())==JFileChooser.APPROVE_OPTION)
            Main.main(new String[]{fc.getSelectedFile().getAbsolutePath()});
    }
}
