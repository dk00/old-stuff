package hw01.b96902120;

import hw01.cup.*;

import static org.junit.Assert.*;
import org.junit.Before;
import org.junit.Test;

public class TypeBdrinkTEST {
    
    Cup cup;

    @Before
    public void setUp() throws Exception {
	cup = new Mug(20, 
	      new Mug(20, 
	      new PaperCup(20, 
	      new PaperCup(20, 
	      new Cup(20, 
	      new Cup(20, 
	      new PaperCup(20, 
	      new Mug(20, null))))))));
    }

    @Test
    public void testTypeBdrink() {
	cup.typeBdrink(10);
	assertEquals("9 8 9 10 10 10 11 10", cup.toString());
	cup.typeBdrink(10);
	assertEquals("0 0 0 0 0 0 2 0", cup.toString());
    }

}
