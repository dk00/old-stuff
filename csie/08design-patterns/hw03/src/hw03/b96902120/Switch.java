package hw03.b96902120;

enum Switch {
    Locked{
        <T> T Select(T A,T B){
            return A;
        }
        Switch Change(){
            return Unlocked;
        }
    },    
    Unlocked{
        <T> T Select(T A,T B){
            return B;
        }
        Switch Change(){
            return Locked;
        }
    };
    Switch timeOut(){
        return Locked;
    }
    abstract <T> T Select(T A,T B);
    abstract Switch Change();
}
