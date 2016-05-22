package hw02.strategy;

public class MallardDuck extends Duck {

    public MallardDuck() {
        flyBehavior = new FlyWithWings();
        quackBehavior = new Quack();
    }

    public String display() {
        return "I'm a real Mallard duck";
    }
}
