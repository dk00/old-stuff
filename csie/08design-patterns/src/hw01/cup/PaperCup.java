package hw01.cup;

public class PaperCup extends Cup {
    
    public PaperCup(int amount, Cup next) {
	super(amount, next);
    }
    
    public void typeAdrink(int n) {
	amount -= n - 1;
	if (amount < 0) amount = 0;
	if (next != null) next.typeAdrink(n);
    }
}
