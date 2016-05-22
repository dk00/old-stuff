package hw02.strategy;

import org.junit.Test;
import static org.junit.Assert.*;

public class DuckTEST {

    @Test
    public void testDuckBehavior() {
        Duck duck;
        
        duck= new DecoyDuck();
        assertEquals("I'm a duck Decoy", duck.display());
        assertEquals("I can't fly", duck.fly());
        assertEquals("<< Silence >>", duck.quack());
        assertEquals("All ducks float, even decoys!", duck.swim());

        duck= new MallardDuck();
        assertEquals("I'm a real Mallard duck", duck.display());
        assertEquals("I'm flying!!", duck.fly());
        assertEquals("Quack", duck.quack());
        assertEquals("All ducks float, even decoys!", duck.swim());
        
        duck= new RedHeadDuck();
        assertEquals("I'm a real Red Headed duck", duck.display());
        assertEquals("I'm flying!!", duck.fly());
        assertEquals("Quack", duck.quack());
        assertEquals("All ducks float, even decoys!", duck.swim());
        
        duck= new RubberDuck();
        assertEquals("I'm a rubber duckie", duck.display());
        assertEquals("I can't fly", duck.fly());
        assertEquals("Squeak", duck.quack());
        assertEquals("All ducks float, even decoys!", duck.swim());
        
        duck= new ModelDuck();
        assertEquals("I'm a model duck", duck.display());
        assertEquals("I can't fly", duck.fly());
        assertEquals("Quack", duck.quack());
        assertEquals("All ducks float, even decoys!", duck.swim());
        duck.useRocket();
        assertEquals("I'm flying with a rocket", duck.fly());
    }

}