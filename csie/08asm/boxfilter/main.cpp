
#include <mygba.h>
#include "input0.h"	//holds the image information in an array
	
extern "C" void boxfilter(u16 *ret,const u16* ori);
extern "C" void myfilter(u16 *ret,const u16* ori);

MULTIBOOT

int main(void)
{
    u16* origin = (u16 *)input_pic;
    u32* out = (u32*)0x02000000;
    u16* filtered = (u16*)0x02000008;
    u16* test = (u16*)0x02012C08;

    u32 t0,tsub;
    u32 x,y;
    u32 result = 0;
    u32 status = 0;

 
	M_TIM0CNT_SPEED_SELECT_SET(0);
	R_TIM1CNT |= 0x0004;
	
    REG_TM0D = 0;
    REG_TM1D = 0;
	M_TIM0CNT_TIMER_START;
	M_TIM1CNT_TIMER_START;
	t0 = (REG_TM1D<<16)+REG_TM0D;
    myfilter(filtered,origin);
    tsub = (REG_TM1D<<16)+REG_TM0D;
    M_TIM0CNT_TIMER_STOP;
    M_TIM1CNT_TIMER_STOP;

    out[0] = result;
    out[1] = tsub;

    boxfilter(test,origin);
    
    for(y=0;y<160;y++) {
        for(x=0;x<240;x++) {
            if( test[240*y+x] != filtered[240*y+x])
			{
				filtered[240*y+x]&=31;
                result = 1;
			}
        }
    }
    
    out[0] = result;
    out[1] = tsub;
    
    ham_Malloc(240*160*2 + 8);
    ham_Init();
    ham_SetBgMode(3);
    ham_LoadBitmap(filtered);
    
    ham_InitPad();
    while(1) {
        ham_UpdatePad();
        if(Pad.Pressed.Down) {
            if(status == 0) {
                status = 1;
            }
            else if(status == 1) {
                ham_DeInitText();
            }
            ham_ResetBg();
            ham_SetBgMode(0);
            ham_InitText(0);
            if(result == 0) ham_DrawText(2,8,"Correct.");
            else    ham_DrawText(2,8,"Wrong.");
            ham_DrawText(2,10,"Clocks : %u",tsub);
            
        }
        if(Pad.Pressed.Up) {
            if(status == 1) {
                ham_DeInitText();
                status = 0;
            }
            ham_SetBgMode(3);
            ham_LoadBitmap(filtered);
        }
        if(Pad.Pressed.Left) {
            if(status == 1) {
                ham_DeInitText();
                status = 0;
            }
            ham_SetBgMode(3);
            ham_LoadBitmap(origin);
        }
        if(Pad.Pressed.Right) {
            break;
        }
    }

    return 0;
}


/* END OF FILE */
