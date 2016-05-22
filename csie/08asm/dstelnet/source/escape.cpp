#include"escape.h"
Escape escape;
int Escape::operator()(Screen &sc,const char *seq){
	if(*seq++=='\x1b'){
		switch(*seq){
			case '[':
				this->sc=&sc;
				this->seq=seq+1;
				return start();
			case 'D':
				sc.Scroll_Up();
				return ESCAPE_OK;
			case 'M':
				sc.Scroll_Down();
				return ESCAPE_OK;
			case '7':
				sc.savx=sc.x;
				sc.savy=sc.y;
				sc.savfc=sc.fc;
				sc.savbc=sc.bc;
				return ESCAPE_OK;
			case '8':
				sc.x=sc.savx;
				sc.y=sc.savy;
				sc.fc=sc.savfc;
				sc.bc=sc.savbc;
				return ESCAPE_OK;
			case 'c':
			case 'H':
			case '(':
			case ')':
				return ESCAPE_NO;
			default:
				return ESCAPE_ERROR;
		}
	}else{
		return ESCAPE_ERROR;
	}
}
int Escape::start(){
	top=0;
	while(1){
		while(*seq==';')
			++seq;
		if(*seq>='0' && *seq<='9'){
			if(top>=10)
				return ESCAPE_ERROR;
			num[top]=*seq++-'0';
			while(*seq>='0' && *seq<='9')
				num[top]=num[top]*10+*seq++-'0';
			++top;
		}else if(*seq=='\"'){
			return ESCAPE_NO;
		}else{
			break;
		}
	}
	return end();
}
int Escape::end(){
	u16 mask=0;
	switch(*seq){
		case 'm':
			if(top==0){
				num[0]=0;
				top=1;
			}
			mask=7|(sc->fc&24);
			sc->fc|=24;
			for(int i=0;i<top;++i){
				if(num[i]>=40){
					sc->bc=num[i]-40;
				}else if(num[i]>=30){
					int t=
					sc->fc=(num[i]-30)|8;
				}else{
					switch(num[i]){
						case 0:
							//¹w³]
							sc->fc=7;
							sc->bc=0;
							mask=7;
							break;
						case 1:
							mask|=8;
							break;
						case 5:
							mask|=16;
							break;
						case 7:
							u16 t=sc->fc;
							sc->fc=sc->bc;
							sc->bc=t&7;
							break;
					}
				}
			}
			sc->fc&=mask;
			return ESCAPE_OK;
		case 'f':
		case 'H':
			if(top>2)
				return ESCAPE_ERROR;
			sc->x=(top>0?num[0]:1)-1;
			sc->y=(top>1?num[1]:1)-1;
			return ESCAPE_OK;
		case 'A':
			if(top>1)
				return ESCAPE_ERROR;
			sc->x-=(top>0?num[0]:1);
			if(sc->x>200)
				sc->x=0;
			return ESCAPE_OK;
		case 'B':
			if(top>1)
				return ESCAPE_ERROR;
			sc->x+=(top>0?num[0]:1);
			if(sc->x>=Maxn)
				sc->x=Maxn-1;
			return ESCAPE_OK;
		case 'C':
			if(top>1)
				return ESCAPE_ERROR;
			sc->y+=(top>0?num[0]:1);
			if(sc->y>=Maxm)
				sc->y=Maxm-1;
			return ESCAPE_OK;
		case 'D':
			if(top>1)
				return ESCAPE_ERROR;
			sc->y-=(top>0?num[0]:1);
			if(sc->y>200)
				sc->y=0;
			return ESCAPE_OK;
		case 's':
			sc->savx=sc->x;
			sc->savy=sc->y;
			return ESCAPE_OK;
		case 'u':
			sc->x=sc->savx;
			sc->y=sc->savy;
			return ESCAPE_OK;
		case 'r':
			sc->Set_Scroll((top>0?num[0]:1)-1,(top>1?num[1]:Maxn)-1);
			return ESCAPE_OK;
		case 'K':
			if(top==0){
				sc->erase(sc->x,sc->y,sc->x,Maxm);
			}else if(num[0]==1){
				sc->erase(sc->x,0,sc->x,sc->y);
			}else if(num[0]==2){
				sc->erase(sc->x,0,sc->x,Maxm);
			}else{
				return ESCAPE_ERROR;
			}
			return ESCAPE_OK;
		case 'J':
			if(top==0){
				sc->erase(sc->x,0,Maxn,Maxm);
			}else if(num[0]==1){
				sc->erase(0,0,sc->x,Maxm);
			}else if(num[0]==2){
				sc->erase(0,0,Maxn,Maxm);
				sc->x=0;
				sc->y=0;
			}else{
				return ESCAPE_ERROR;
			}
			return ESCAPE_OK;
		case 'i':
		case 'p':
		case 'g':
		case 'h':
		case 'l':
		case 'c':
		case 'n':
			return ESCAPE_NO;
		default:
			return ESCAPE_ERROR;
	}
}
