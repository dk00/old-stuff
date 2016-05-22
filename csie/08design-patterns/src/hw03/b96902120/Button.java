package hw03.b96902120;

public enum Button{
    HotWaterLock{
        MachineState pressAct(MachineState M){
            return M.hotLock();
        }
    },
    ShowTemp{
        MachineState pressAct(MachineState M){
            return M.showTemp();
        }        
    },
    Cont{
        MachineState pressAct(MachineState M){
            return M.toggleCont();
        }
    },
    HotWater{
        MachineState pressAct(MachineState M){
            return M.toggleHot();
        }
        MachineState releaseAct(MachineState M){
            return M.buttonRelease();
        }
    },
    WarmWater{
        MachineState pressAct(MachineState M){
            return M.toggleWarm();
        }        
        MachineState releaseAct(MachineState M){
            return M.buttonRelease();
        }
    },
    ColdWater{
        MachineState pressAct(MachineState M){
            return M.toggleCold();
        }        
        MachineState releaseAct(MachineState M){
            return M.buttonRelease();
        }
    };
    MachineState releaseAct(MachineState M){
        return M;
    }
    MachineState pressAct(MachineState M){
        return M;
    }
}
