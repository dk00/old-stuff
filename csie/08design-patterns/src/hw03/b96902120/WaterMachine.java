package hw03.b96902120;

public class WaterMachine{
    MachineState mState=MachineState.StandBy;
    Button Current=null;
    public void press(Button b){
        if(Current==null)
        {
            Current=b;
            mState=b.pressAct(mState);
        }
    }
    public void release(Button b){
        if(Current==b){
            Current=null;
            mState=b.releaseAct(mState);
        }
    }
    public void press_release(Button b){
        press(b);
        release(b);
    }
}
