package hw02.b96902120;

public class DecoyDuck extends Duck{
    {
        canFly=false;
    }
    public String display(){
        return "I'm a duck Decoy";
    }
    public String quack(){
        return "<< Silence >>";
    }
    public String swim(){
        return "All ducks float, even decoys!";
    }
}
