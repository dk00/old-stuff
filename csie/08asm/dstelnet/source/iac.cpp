#define SE 240
#define NOP 241
#define DATA_MARK 242
#define BREAK 243
#define INTERRUPT_PROCESS 244
#define ABORT_OUTPUT 245
#define ARE_YOU_THERE 246
#define ERASE_CHARACTER 247
#define ERASE_LINE 248
#define GO_AHEAD 249
#define SB 250
#define WILL 251
#define WONT 252
#define DO 253
#define DONT 254
#define IAC 255
#include<sys/socket.h>
void Send(int sd,const char buf[],int n);
void iac(int sc,const char *ptr){
	char r3[3]={IAC};
	++ptr;
	switch(*ptr){
		case WILL:
			++ptr;
//-			r3[1]=(*ptr==1||*ptr==3)?DO:DONT;
			r3[1]=(*ptr==3)?DO:DONT;
			r3[2]=*ptr;
			send(sc,r3,sizeof(r3),0);
			break;
		case WONT:
			break;
		case DO:
			++ptr;
			r3[1]=(*ptr==24||*ptr==31)?WILL:WONT;
			r3[2]=*ptr;
			send(sc,r3,sizeof(r3),0);
			if(*ptr==31){
				char ws[]={IAC,SB,0,80,0,24,IAC,SE};
				send(sc,ws,sizeof(ws),0);
			}
			break;
		case DONT:
			break;
		case SB:
			++ptr;
			if(*ptr==24 && *(ptr+1)==1){
				char ws[]={IAC,SB,24,0,'U','N','K','N','O','W','N',IAC,SE};
				//char ws[]={IAC,SB,24,0,'V','T','1','0','0',IAC,SE};
				send(sc,ws,sizeof(ws),0);
			}
			break;
	}
}
