function DoCast(which,usehand,x,y,placeholder) {

	//print (typeof(which));
	if (typeof(which)=="string") usehand_adder=0;
	if (typeof(which)=="number") usehand_adder=2;

	for(var j=0; j<5; j++) {
		for (var qw = 0; qw < 100; qw++) {
			if(!me.itemoncursor) break;
			DoDel(75);
		}

		if(me.itemoncursor) return false;
		if(arguments.length>1) dprint("Casting "+which+" on hand number "+usehand);

		for(var sw=0; sw<3; sw++) {
			if(me.getSkill(usehand+usehand_adder)!=which) {

				//if(!me.getSkill(which,1)) return false; // uses only real given skill points
				if(!me.getSkill(which,0)) return false; // uses all skill points available for this skill
				dprint("Switching to "+which+" on hand number "+usehand);

				me.setSkill(which,usehand);
//				for (var qw = 0; qw < 25; qw++) {
				for (var qw = 0; qw < (spelltimeout/10); qw++) {
					if(me.getSkill(usehand+usehand_adder)==which) break;
					DoDel(75);
				}
				if(me.getSkill(usehand+usehand_adder)!=which) return false;
			}
		}

		// 1 standing still outside, 5 standing still in town
		waitloops=0;
		while (me.mode!=1 && me.mode!=5 && waitloops<=20) {
			waitloops++;
			delay(100);
		}

		if (usehand==0) {		//right button
			mouse_down=3;
			mouse_up=5;
			shift=0;
		} else {			//left button
			mouse_down=0;
			mouse_up=2;
			shift=1;
		}

		switch(arguments.length)
		{
			// invalid
			case 0:
			case 1: break;
			// casting on me
			case 2: clickMap(mouse_down, shift, me.x+rnd(-2,2), me.y+rnd(-2,2));
				DoDel(75);
				clickMap(mouse_up, shift, me.x+rnd(-2,2), me.y+rnd(-2,2));
				break;
			// casting on monster/item/object
			case 3:	clickMap(mouse_down, shift, x);
				DoDel(75);
				clickMap(mouse_up, shift, x.x+rnd(-2,2), x.y+rnd(-2,2));
				break;
			// casting on location (x/y)
			case 4: clickMap(mouse_down, shift, x, y);
				DoDel(75);
				clickMap(mouse_up, shift, x, y);
				break;
			// casting on hireling - shouldn't be needed anymore
			case 5:	x.useSkill(0);
				DoDel(75);
				clickMap(mouse_up, shift, x.x, x.y); //mouse up
				break;
		}
		/*switch(arguments.length)
		{
			case 0: break;
			case 2: me.useSkillAt(me.x+rnd(-2,2),me.y+rnd(-2,2),usehand); break;
			case 3:	x.useSkill(usehand);
				DisplayEnemyLife(x);
				break;
			case 4: me.useSkillAt(x,y,usehand); break;
		}*/
		mcheck=PreModeWait();
		if(!mcheck)
			dprint("Cast has failed of "+which+" on hand number "+usehand);
		else
		{
			dprint("Cast reported succesful of "+which+" on hand number "+usehand);
			while (me.mode==mcheck)
			{
				if(target)
				{
					DisplayEnemyLife(target);
					if (target.hp <= 1) return true;
				}
				DoDel(75);
			}
			return true;
		}
	}
	return false;
}
