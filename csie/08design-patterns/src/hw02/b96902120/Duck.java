package hw02.b96902120;

public abstract class Duck{
    static Boolean usingRocket=false,canFly;
    public abstract String display();
    public String fly(){
            return usingRocket?"I'm flying with a rocket":
                canFly?"I'm flying!!":"I can't fly";
    }
    public abstract String quack();
    public abstract String swim();
    public void useRocket(){
        usingRocket=true;
    }
}
