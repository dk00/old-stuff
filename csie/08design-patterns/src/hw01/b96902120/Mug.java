package hw01.b96902120;
public class Mug extends Cup {
    public Mug(int amount, Cup next) {
        super(amount, next);
    }
    public void typeBdrink(int n) {
        amount -= n + 1;
        if(amount < 0) amount = 0;
        if(next != null)
            next.typeBdrink(n+1);
    }    
}
