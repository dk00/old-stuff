package hw03.b96902120;

enum MachineState{
    StandBy{
        
    },
    HotWater{
        MachineState toggleCont(){
            return stop();
        }
        MachineState toggleCold(){
            return stop();
        }
        MachineState toggleWarm(){
            return stop();
        }
        MachineState toggleHot(){
            return stop();
        }
    },
    WarmWater{
        MachineState toggleCont(){
            return stop();
        }
        MachineState toggleCold(){
            return stop();
        }
        MachineState toggleWarm(){
            return stop();
        }
        MachineState toggleHot(){
            return stop();
        }       
    },
    ColdWater{
        MachineState toggleCont(){
            return stop();
        }
        MachineState toggleCold(){
            return stop();
        }
        MachineState toggleWarm(){
            return stop();
        }
        MachineState toggleHot(){
            return stop();
        }
    };
    Display dState=Display.Hot;
    Switch hState=Switch.Locked,cState=Switch.Locked;    
    MachineState set(Display d,Switch c,Switch h){
        dState=d;
        hState=h;
        cState=c;
        return this;
    }
    MachineState stop(){
        hState=Switch.Locked;
        cState=Switch.Locked;
        return StandBy.set(dState,cState,hState);
    }
    MachineState showTemp(){
        dState=dState.showNext();
        return this;
    }
    MachineState toggleHot(){
        dState=hState.Select(dState,Display.Hot);
        return (hState.Select(this,HotWater)).set(dState,cState,hState);
    }
    MachineState toggleWarm(){
        dState=Display.Warm;
        return WarmWater.set(dState,cState,hState);
    }
    MachineState toggleCold(){
        dState=Display.Cold;
        return ColdWater.set(dState,cState,hState);
    }
    MachineState timeOut(){
        dState=dState.timeOut();
        cState=cState.timeOut();
        hState=hState.timeOut();
        return StandBy.set(dState,cState,hState);
    }
    MachineState toggleCont(){
        cState=cState.Change();
        return this;
    }
    MachineState hotLock(){
        dState=Display.Hot;
        hState=hState.Change();
        return this;
    }
    MachineState buttonRelease(){
        hState=cState.Select(Switch.Locked,hState);
        return cState.Select(StandBy,this).set(dState,cState,hState);
    }
}
