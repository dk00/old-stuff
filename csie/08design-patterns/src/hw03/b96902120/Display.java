package hw03.b96902120;

public enum Display {
    Hot{
        public Display showNext(){
            return Display.Warm;
        }
    },
    Warm{
        public Display showNext(){
            return Display.Cold;
        }    
    },
    Cold{
        public Display showNext(){
            return Display.Hot;
        }        
    };
    public Display timeOut(){
        return Hot;
    }
    public abstract Display showNext();
}
