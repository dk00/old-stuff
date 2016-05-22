#include "scrctrl.h"

#define BOARD 8

extern bool check(char map[BOARD][BOARD],bool chess,int x,int y);
extern void caln(char map[BOARD][BOARD],int &cnum,int &ynum);


//	define chess
#define BLACK 1
#define WHITE 0
#define NONE 2

extern int AI;
extern int lastx,lasty;

char tmpmap[BOARD][BOARD];

void drawgrid()
{
	cls();
	color(C_LIGHTGRAY,C_BLACK);
	locate(1,32);	myPuts("Othello AI v3.0");
	locate(10,60);	myPuts("Ctrl+Z: 悔棋");
	locate(12,60);	myPuts("F2: 重開一局");
	locate(14,60);	myPuts("Esc: 結束程式");
	locate(20,60);	myPuts("Powered by");
	locate(21,63);	myPuts("雄中電研 CSTRC");
	locate(2,23);	myPuts("┌─┬─┬─┬─┬─┬─┬─┬─┐");
	for(int i=0; i<8; i++)
	{
		locate(i*2+3,23);	myPuts("│  │  │  │  │  │  │  │  │");
		if(i!=8)
			locate(i*2+4,23);	myPuts("├─┼─┼─┼─┼─┼─┼─┼─┤");
	}
	locate(18,23);	myPuts("└─┴─┴─┴─┴─┴─┴─┴─┘");
}

void paintboard(char map[BOARD][BOARD],int &cnum,int &ynum, bool chess)
{
	int i,j;
	drawgrid();
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			locate(2*i+3,4*j+25);
			if(chess==WHITE) if(i==lastx && j==lasty) color(C_GREEN,C_UNCHANGE); else color(C_LIGHTGRAY,C_UNCHANGE);
			if(map[i][j]==BLACK)
			{
				myPuts("●");
				tmpmap[i][j]=map[i][j];
			}
			else if(map[i][j]==WHITE)
			{
				myPuts("○");
				tmpmap[i][j]=map[i][j];
			}
			else if(map[i][j]==NONE && check(map,chess,i,j)==1)
			{
				myPuts("。");
				tmpmap[i][j]=3;
			}
			else
				tmpmap[i][j]=map[i][j];
		}
	}
	caln(map,cnum,ynum);
	color(C_LIGHTGRAY,C_UNCHANGE);
	locate(3,60); _myPuts("●電腦：%2d",cnum);
	locate(5,60); _myPuts("○玩家：%2d",ynum);
//	locate(3,5); _myPuts("電腦等級：%2d",AI);
	locate(3,3);
	if(AI==4)
		_myPuts("AI level：Beginner");
	else if(AI==6)
		_myPuts("AI level：Normal");
	else if(AI==7)
		_myPuts("AI level：Advanced");
	else
		_myPuts("AI level：Master");
}

int nowposx=2;
int nowposy=3;

void returnpos(bool start)
{
	nowposx=2;
	nowposy=3+start;
}

void _showone(char grid)
{
	switch(grid)
	{
	case BLACK:
		myPuts("●");
		break;
	case WHITE:
		myPuts("○");
		break;
	case NONE:
		myPuts("  ");
		break;
	case 3:
		myPuts("。");
		break;
	}
}

int getInput(int &bestx, int &besty)
{
	int c;
	while(1)
	{
		locate(nowposx*2+3,nowposy*4+25);
		color(C_LIGHTGRAY,C_MAGENTA);
		if(nowposx==lastx && nowposy==lasty) color(C_GREEN,C_UNCHANGE);
		_showone(tmpmap[nowposx][nowposy]);
		do
		{
			c=inkey();
		} while(c!=UP && c!=DOWN && c!=LEFT && c!=RIGHT && c!=13 && c!=' ' && c!=26 && c!=27 && c!=F2);
		locate(nowposx*2+3,nowposy*4+25);
		color(C_LIGHTGRAY,C_BLACK);
		if(nowposx==lastx && nowposy==lasty) color(C_GREEN,C_UNCHANGE);
		_showone(tmpmap[nowposx][nowposy]);
		switch(c)
		{
		case UP:
			if(nowposx>0) nowposx--; else nowposx=BOARD-1;
			break;
		case DOWN:
			if(nowposx<BOARD-1) nowposx++; else nowposx=0;
			break;
		case LEFT:
			if(nowposy>0) nowposy--; else nowposy=BOARD-1;
			break;
		case RIGHT:
			if(nowposy<BOARD-1) nowposy++; else nowposy=0;
			break;
		case 26:	//Ctrl-Z
			return 2;
		case 27:	//Esc
			return -1;
		case F2:	//F2
			return 3;
		default:  //case 13:  case ' ': //Enter and space
			bestx=nowposx;
			besty=nowposy;
			return 0;
		}
	}
}
