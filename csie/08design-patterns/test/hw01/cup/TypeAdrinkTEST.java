package hw01.cup;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class TypeAdrinkTEST {

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
    public void testTypeAdrink() {
        cup.typeAdrink(10);
        assertEquals("9 9 11 11 10 10 11 9", cup.toString());
        cup.typeAdrink(10);
        assertEquals("0 0 2 2 0 0 2 0", cup.toString());
    }
}
