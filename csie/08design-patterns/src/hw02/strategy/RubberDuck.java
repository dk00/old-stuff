package hw02.strategy;

public class RubberDuck extends Duck {

    public RubberDuck() {
        flyBehavior = new FlyNoWay();
        quackBehavior = new Squeak();
    }

    public String display() {
        return "I'm a rubber duckie";
    }
}
