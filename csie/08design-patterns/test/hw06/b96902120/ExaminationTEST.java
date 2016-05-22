package hw06.b96902120;

import java.io.*;
import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class ExaminationTEST {

    @Test
    public void checkExamination() {
	Examination exam = new Examination("examination.xml");
	String result = null;
	try {
	    FileReader fr = new FileReader("result");
	    BufferedReader br = new BufferedReader(fr);
	    result = br.readLine();
	} catch (IOException e) {
	}
	assertEquals(result, exam.listTop());
    }
    
}
