package hw03.b96902120;
import org.junit.Test;
import static org.junit.Assert.*;

public class test0 {
    @Test
    public void WarmWaterTest(){
        WaterMachine M0=new WaterMachine();
        assertEquals(M0.mState.cState,Switch.Locked);
        M0.press_release(Button.Cont);
        assertEquals(M0.mState.cState,Switch.Unlocked);
        M0.press(Button.WarmWater);
        assertEquals(M0.mState,MachineState.WarmWater);
        assertEquals(M0.mState.cState,Switch.Unlocked);
        M0.release(Button.WarmWater);
        assertEquals(M0.mState,MachineState.WarmWater);
        assertEquals(M0.mState.cState,Switch.Unlocked);
        M0.press(Button.WarmWater);
        assertEquals(M0.mState.cState,Switch.Locked);
        assertEquals(M0.mState.hState,Switch.Locked);
        assertEquals(M0.mState,MachineState.StandBy);
    }
    @Test
    public void ColdWaterTest()
    {
        WaterMachine M0=new WaterMachine();
        M0.press_release(Button.Cont);
        M0.press_release(Button.Cont);
        M0.press(Button.ColdWater);
        assertEquals(M0.mState,MachineState.ColdWater);
        M0.release(Button.ColdWater);
        assertEquals(M0.mState,MachineState.StandBy);
    }
    @Test
    public void HotWaterTest(){
        WaterMachine M0=new WaterMachine();
        assertEquals(M0.mState,MachineState.StandBy);
        M0.press(Button.HotWater);
        assertEquals(M0.mState,MachineState.StandBy);
        M0.release(Button.HotWater);
        M0.press_release(Button.HotWaterLock);
        assertEquals(M0.mState.hState,Switch.Unlocked);
        M0.press(Button.HotWater);
        assertEquals(M0.mState,MachineState.HotWater);
        assertEquals(M0.mState.hState,Switch.Unlocked);
        assertEquals(M0.Current,Button.HotWater);
        M0.release(Button.HotWater);
        assertEquals(M0.Current,null);
        assertEquals(M0.mState,MachineState.StandBy);
        assertEquals(M0.mState.hState,Switch.Locked);
        M0.press_release(Button.HotWaterLock);
        M0.press_release(Button.Cont);
        M0.press(Button.HotWater);
        assertEquals(M0.mState.cState,Switch.Unlocked);
        assertEquals(M0.mState.hState,Switch.Unlocked);
        assertEquals(M0.mState,MachineState.HotWater);
        M0.release(Button.HotWater);
        assertEquals(M0.mState.cState,Switch.Unlocked);
        assertEquals(M0.mState.hState,Switch.Unlocked);
        assertEquals(M0.mState,MachineState.HotWater);
        M0.press_release(Button.Cont);
        assertEquals(M0.mState.cState,Switch.Locked);
        assertEquals(M0.mState.hState,Switch.Locked);
        assertEquals(M0.mState,MachineState.StandBy);
    }
    @Test
    public void ShowTempTest(){
        WaterMachine M0=new WaterMachine();
        assertEquals(M0.mState.dState,Display.Hot);
        M0.press_release(Button.ShowTemp);
        assertEquals(M0.mState.dState,Display.Warm);
        M0.press_release(Button.ShowTemp);
        assertEquals(M0.mState.dState,Display.Cold);
        M0.press(Button.HotWater);
        assertEquals(M0.mState.dState,Display.Cold);
        M0.release(Button.HotWater);
        M0.press(Button.WarmWater);
        assertEquals(M0.mState.dState,Display.Warm);
        M0.release(Button.WarmWater);
        M0.press_release(Button.HotWaterLock);
        assertEquals(M0.mState.dState,Display.Hot);
        M0.press(Button.ColdWater);
        assertEquals(M0.mState.dState,Display.Cold);
        M0.release(Button.ColdWater);        
    }
}
