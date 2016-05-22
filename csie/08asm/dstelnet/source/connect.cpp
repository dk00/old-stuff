#include<nds.h>
#include<netdb.h>
#include<dswifi9.h>
#include"mes.h"
#include"text.h"
extern u32 keysPress();
extern void getTouch(short &x,short &y);
void t50(void){Wifi_Timer(50);}
void arm9_sync(){REG_IPC_FIFO_TX=0x87654321;}
void arm9_fifo(){
   u32 value=REG_IPC_FIFO_RX;
   if(value==0x87654321)Wifi_Sync();
}
void Wifi_Init()
{
	REG_IPC_FIFO_CR = IPC_FIFO_ENABLE | IPC_FIFO_SEND_CLEAR; // enable & clear FIFO	
	u32 Wifi_pass= Wifi_Init(WIFIINIT_OPTION_USELED);
   	REG_IPC_FIFO_TX=0x12345678;
   	REG_IPC_FIFO_TX=Wifi_pass;
	*((volatile u16 *)0x0400010E) = 0; // disable timer3
	//irqInit(); 
	irqSet(IRQ_TIMER3,t50); // setup timer IRQ
	irqEnable(IRQ_TIMER3);
   	irqSet(IRQ_FIFO_NOT_EMPTY, arm9_fifo); // setup fifo IRQ
   	irqEnable(IRQ_FIFO_NOT_EMPTY);
   	REG_IPC_FIFO_CR = IPC_FIFO_ENABLE | IPC_FIFO_RECV_IRQ; // enable FIFO IRQ
   	Wifi_SetSyncHandler(arm9_sync); // tell wifi lib to use our handler to notify arm7
	// set timer3
	*((volatile u16 *)0x0400010C) = -6553; // 6553.1 * 256 cycles = ~50ms;
	*((volatile u16 *)0x0400010E) = 0x00C2; // enable, irq, 1/256 clock
	while(Wifi_CheckInit()==0) // wait for arm7 to be initted successfully
		swiWaitForVBlank();
}
const char *tostr(const Wifi_AccessPoint &ap)
{
	static char buf[64];
	int i=0;	
	for(i=0;i<32 && i<ap.ssid_len;i++)
		buf[i]=ap.ssid[i];
	for(;i<32;i++)
		buf[i]=' ';
	buf[32]=0;
	return buf;
}
Screen &out=Sub;
int ConnectAP(Wifi_AccessPoint &ap)
{
	printf(out,"\x1b[11;1f%s",Mes::connecting);
	Wifi_SetIP(0,0,0,0,0);
	int res=Wifi_ConnectAP(&ap,0,0,0);
	if(res)return res;
	while(1)
	{
		int stat=Wifi_AssocStatus();
		printf(out,"\x1b[12;1f%s",Mes::stat_str[stat]);
		if(stat==ASSOCSTATUS_ASSOCIATED || stat==ASSOCSTATUS_CANNOTCONNECT)
			break;
		if(keysPress()&KEY_B)
		{
			printf(out,"\x1b[12;1f%s\x1b[K",Mes::abort);
			break;
		}
		swiWaitForVBlank();
	}
	if(Wifi_AssocStatus()!=ASSOCSTATUS_ASSOCIATED)res=1;
	if(res)
	{
		Wifi_DisconnectAP();
		printf(out,"\x1b[11;1f%s",Mes::nconnect);
	}
	else printf(out,"\x1b[11;1f%s",Mes::connected);
	return res;
}
int SelectAP()
{
	printf(out,Mes::init_wifi);
	Wifi_Init();
	Wifi_ScanMode();
	printf(out,Mes::done);
	int i,j=0,k=0,page=0,n;
	Wifi_AccessPoint ap[8];
	while(1)
	{
		n=Wifi_GetNumAP();
		printf(out,Mes::select_ap,n);
		while(page>0 && (page*8+k>=n))page--;
		while(page+k>=n)k--;
		for(i=0;i<8 && 8*page+i<n;i++)
		{
			Wifi_GetAPData(8*page+i,ap+i);
			printf(out,"%c[%d]%s\r\n",(i==k)?'>':' ',(ap[i].rssi*100)/0xD0,tostr(ap[i]));
		}
		for(;i<8;i++)
			printf(out,"\x1b[2K\r\n");
		scanKeys();
		u32 press=keysDownRepeat();
		if(press&(KEY_A|KEY_RIGHT))
			if(ConnectAP(ap[k])==0)
			{
				printf(out,"\x1b[2J");
				return 0;
			}
		if(press&KEY_UP)k--;
		if(press&KEY_DOWN)k++;
		if(page*8+k>=n)k--;
		if(k<0)
		{
			if(page>0)page--,k=7;
			else k=0;
		}
		if(k>=8)
		{
			if((page+1)*8<n)page++,k=0;
			else k=7;
		}
		printf(out,"\x1b[11;1fpage %d/%d\x1b[K",page+1,(n+7)/8);
		swiWaitForVBlank();
	}
	return -1;
}
