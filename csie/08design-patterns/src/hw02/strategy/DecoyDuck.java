package hw02.strategy;

public class DecoyDuck extends Duck {

    public DecoyDuck() {
        setFlyBehavior(new FlyNoWay());
        setQuackBehavior(new MuteQuack());
    }

    public String display() {
        return "I'm a duck Decoy";
    }
}
