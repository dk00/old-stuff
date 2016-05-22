package hw02.strategy;

public class MuteQuack implements QuackBehavior {

    public String quack() {
        return "<< Silence >>";
    }
}
