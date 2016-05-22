package hw01.b96902120;
public class Cup{    
    public int amount;
    public Cup next;
    public Cup(int amount, Cup next) {
        this.amount = amount;
        this.next = next;
    }
    public void typeBdrink(int n) {
        amount -= n;
        if (amount < 0) amount = 0;
        if (next != null) next.typeBdrink(n);
    }
    public String toString() {
        if (next == null) return amount + "";
        return amount + " " + next.toString();
    }   
}
