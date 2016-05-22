#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//+
#include "scrctrl.h"

#define FinalCondition1 4/5-6
#define FinalCondition2 8
#define CORNER 2000
#define EDGE 100
#define MIDOUT 1
//#define MIDDLE 3

//  simply a big odd integer
#define ODD 25

//  define BinarySearchDefault
#define BSD 4

//	define diagonly
#define DIAGON

//	define level
#define MAX 1
#define MIN 0

//	define chess
#define BLACK 1
#define WHITE 0
#define NONE 2


//	define direct
#ifdef DIAGON
#define DIRECT 8
#else
#define DIRECT 4
#endif

//	define cross
#define CROSS

//	define board size
#define BOARD 8

/*
#ifndef bool
#define bool char
#endif
*/

extern int getInput(int &bestx, int &besty);
extern void paintboard(char map[BOARD][BOARD],int &cnum,int &ynum, bool chess);
extern void returnpos(bool start);

const int plusx[8]={0,0,1,-1,1,1,-1,-1};
const int plusy[8]={1,-1,0,0,1,-1,1,-1};

const short int scoretable[BOARD+1][BOARD]={ {  75,  -6,   6,   4,   4,   6,  -6,  75},
                                             {  -6, -32,  -1,  -1,  -1,  -1, -32,  -6},
                                             {   6,  -1,   0,   0,   0,   0,  -1,   6},
                                             {   4,  -1,   0,   0,   0,   0,  -1,   4},
                                             {   4,  -1,   0,   0,   0,   0,  -1,   4},
                                             {   6,  -1,   0,   0,   0,   0,  -1,   6},
                                             {  -6, -32,  -1,  -1,  -1,  -1, -32,  -6},
		          		                     {  75,  -6,   6,   4,   4,   6,  -6,  75},
                                             {   4,   2,   1,   4,  12,   8,   0,   0} };
//the last line for special scores

int AI;
int bestx=-1,besty=-1;
int lastx,lasty;
int Final;
int result;

void caln(char map[BOARD][BOARD],int &cnum,int &ynum)
{
	int i,j;
	cnum=0;
	ynum=0;
	for(i=0;i<BOARD;i++)
	{
		for(j=0;j<BOARD;j++)
		{
			if(map[i][j]==BLACK)
				cnum++;
			else if(map[i][j]==WHITE)
				ynum++;
		}
	}
}

bool check(char map[BOARD][BOARD],bool chess,int x,int y)
{
	int i;
	bool flag=0;
	int tmpx,tmpy;
	for(i=0;i<DIRECT;i++)
	{
		tmpx=x;
		tmpy=y;
		flag=0;
		while(1)
		{
			tmpx=tmpx+plusx[i];
			tmpy=tmpy+plusy[i];
			if(tmpx<0||tmpx>BOARD-1||tmpy<0||tmpy>BOARD-1)
				break;
			if(map[tmpx][tmpy]==(char)!chess)
				flag=1;
			if(map[tmpx][tmpy]==(char)chess)
			{
				if(flag==0)
					break;
				else if(flag==1)
					return 1;
			}
			else if(map[tmpx][tmpy]==NONE)
				break;
		}
	}
	return 0;
}

/*
void paintboard(char map[BOARD][BOARD],int &cnum,int &ynum, bool chess)
{
	int i,j;
	printf("  ");
	for(i=0;i<BOARD;i++)
		printf("%d",i);
	printf("\n");
	for(i=0;i<BOARD;i++)
	{
		printf("%d ",i);
		for(j=0;j<BOARD;j++)
		{
			if(map[i][j]==BLACK)
				printf("X");
			else if(map[i][j]==WHITE)
				printf("O");
			else if(map[i][j]==NONE&&check(map,chess,i,j)==1)
				printf("-");
			else if(map[i][j]==NONE)
				printf(".");
		}
		printf("\n");
	}
	caln(map,cnum,ynum);
	printf("Computer: %d,You: %d\n",cnum,ynum);
}*/

void cover(char map[BOARD][BOARD],int x,int y,bool chess)
{
	int i;
	bool flag;
	int tmpx,tmpy;
	map[x][y]=chess;
	for(i=0;i<DIRECT;i++)
	{
		tmpx=x;
		tmpy=y;
		flag=0;
		while(1)
		{
			tmpx=tmpx+plusx[i];
			tmpy=tmpy+plusy[i];
			if(tmpx<0||tmpy<0||tmpx>BOARD-1||tmpy>BOARD-1)
				break;
			if(map[tmpx][tmpy]==(char)chess)
			{
				flag=1;
				break;
			}
			else if(map[tmpx][tmpy]==NONE)
				break;
		}
		if(flag==1)
		{
			tmpx=x;
			tmpy=y;
			while(1)
			{
				tmpx=tmpx+plusx[i];
				tmpy=tmpy+plusy[i];
				if(tmpx<0||tmpy<0||tmpx>BOARD-1||tmpy>BOARD-1)
					break;
				if(map[tmpx][tmpy]==(char)chess)
					break;
				else if(map[tmpx][tmpy]==NONE)
					break;
				else if(map[tmpx][tmpy]!=NONE&&map[tmpx][tmpy]!=(char)chess)
					map[tmpx][tmpy]=chess;
			}
		}
	}
}

int cal(char map[BOARD][BOARD])
{
	int score=0;
	int i,j;
	if(Final>0)
	{
		if(Final==2)
		{
			for(i=0;i<BOARD;i++)
			{
				for(j=0;j<BOARD;j++)
				{
					if(map[i][j]==BLACK)
						score+=1;
					else if(map[i][j]==WHITE)
						score-=1;
				}
			}
			return score;
		}
		for(i=0;i<BOARD;i++)
		{
			for(j=0;j<BOARD;j++)
			{
				if(map[i][j]==BLACK)
					score+=scoretable[i][j]+scoretable[BOARD][2];
				else if(map[i][j]==WHITE)
					score-=scoretable[i][j]+scoretable[BOARD][2];
			}
		}
	}
	else
	{
		for(i=0;i<BOARD;i++)
		{
			for(j=0;j<BOARD;j++)
			{
				if(map[i][j]==BLACK)
					score+=scoretable[i][j];
				else if(map[i][j]==WHITE)
					score-=scoretable[i][j];
			}
		}
	}
	int ychoice=0,cchoice=0;
	for(i=0;i<BOARD;i++)
	{
		for(j=0;j<BOARD;j++)
		{
			if(map[i][j]==NONE)
			{
				if(check(map,BLACK,i,j)==1)
					cchoice++;
				if(check(map,WHITE,i,j)==1)
					ychoice++;
			}
		}
	}
	if(cchoice==0 && ychoice==0)
	{
		score=(AI%2)*scoretable[BOARD][4]-scoretable[BOARD][4]/2;
		for(i=0;i<BOARD;i++)
		{
			for(j=0;j<BOARD;j++)
			{
				if(map[i][j]==BLACK)
					score+=scoretable[BOARD][5];
				else if(map[i][j]==WHITE)
					score-=scoretable[BOARD][5];
			}
		}
		return score;
	}
	else
	{
		if(cchoice==0)
			score-=scoretable[BOARD][4];
		else if(ychoice==0)
			score+=scoretable[BOARD][4];
		score+=(cchoice-ychoice)*scoretable[BOARD][3];
	}
	if(map[0][0]!=NONE)
	{
		if(map[0][1]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[0][1];
		else if(map[0][1]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[0][1];
		if(map[1][0]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[1][0];
		else if(map[1][0]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[1][0];
		if(map[1][1]==BLACK)
			score+=scoretable[BOARD][1]-scoretable[1][1];
		else if(map[1][1]==WHITE)
			score-=scoretable[BOARD][1]-scoretable[1][1];
	}
	if(map[0][BOARD-1]!=NONE)
	{
		if(map[0][BOARD-2]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[0][BOARD-2];
		else if(map[0][BOARD-2]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[0][BOARD-2];
		if(map[1][BOARD-1]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[1][BOARD-1];
		else if(map[1][BOARD-1]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[1][BOARD-1];
		if(map[1][BOARD-2]==BLACK)
			score+=scoretable[BOARD][1]-scoretable[1][BOARD-2];
		else if(map[1][BOARD-2]==WHITE)
			score-=scoretable[BOARD][1]-scoretable[1][BOARD-2];
	}
	if(map[BOARD-1][0]!=NONE)
	{
		if(map[BOARD-1][1]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[BOARD-1][1];
		else if(map[BOARD-1][1]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[BOARD-1][1];
		if(map[BOARD-2][0]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[BOARD-2][0];
		else if(map[BOARD-2][0]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[BOARD-2][0];
		if(map[BOARD-2][1]==BLACK)
			score+=scoretable[BOARD][1]-scoretable[BOARD-2][1];
		else if(map[BOARD-2][1]==WHITE)
			score-=scoretable[BOARD][1]-scoretable[BOARD-2][1];
	}
	if(map[BOARD-1][BOARD-1]!=NONE)
	{
		if(map[BOARD-1][BOARD-2]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[BOARD-1][BOARD-2];
		else if(map[BOARD-1][BOARD-2]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[BOARD-1][BOARD-2];
		if(map[BOARD-2][BOARD-1]==BLACK)
			score+=scoretable[BOARD][0]-scoretable[BOARD-2][BOARD-1];
		else if(map[BOARD-2][BOARD-1]==WHITE)
			score-=scoretable[BOARD][0]-scoretable[BOARD-2][BOARD-1];
		if(map[BOARD-2][BOARD-2]==BLACK)
			score+=scoretable[BOARD][1]-scoretable[BOARD-2][BOARD-2];
		else if(map[BOARD-2][BOARD-2]==WHITE)
			score-=scoretable[BOARD][1]-scoretable[BOARD-2][BOARD-2];
	}
	return score;
}

struct sorted
{
	int i,j;
	int random;
};

int compare(const void *a, const void *b){return ((sorted *)a)->random-((sorted *)b)->random;}

bool stuckcut;
bool win_lose(int level, const int score, char map[BOARD][BOARD], bool type)
{
	int i,j;
	char tmp[BOARD][BOARD];
	bool flag=0;
	if(level>=ODD*AI && (level-AI)%2==0)
	{
		if(Final<2 || level>=ODD*(AI+FinalCondition2))
		{
			if(cal(map)>=score)
				return 1;
			else
				return 0;
		}
	}
	if(level==0)
	{
		sorted choice[BOARD*BOARD];
		int pointer=0;
		for(i=0;i<BOARD;i++)
		{
			for(j=0;j<BOARD;j++)
			{
				if(map[i][j]==NONE&&check(map,BLACK,i,j)==1)
				{
					memmove(tmp,map,sizeof(char)*BOARD*BOARD);
					cover(tmp,i,j,BLACK);
					choice[pointer].i=i;
					choice[pointer].j=j;
					choice[pointer++].random=rand();
				}
			}
		}
		qsort(choice, pointer, sizeof(sorted), compare);
		stuckcut=0;
		for(pointer=pointer-1;pointer>=0;pointer--)
		{
			i=choice[pointer].i;
			j=choice[pointer].j;
			memmove(tmp,map,sizeof(char)*BOARD*BOARD);
			cover(tmp,i,j,BLACK);
			if(win_lose(level+ODD,score,tmp,MIN)==1)
			{
				bestx=i;
				besty=j;
				return 1;
			}
		}
		return 0;
	}
	else
	{
		if(type==MAX)
		{
			flag=0;
			for(i=0;i<BOARD;i++)
			{
				for(j=0;j<BOARD;j++)
				{
					if(map[i][j]==NONE&&check(map,BLACK,i,j)==1)
					{
						stuckcut=0;
						memmove(tmp,map,sizeof(char)*BOARD*BOARD);
						cover(tmp,i,j,BLACK);
						if(win_lose(level+ODD,score,tmp,MIN)==1)
							return 1;
						flag=1;
					}
				}
			}
			if(flag==0)
			{
				if(stuckcut==1)
				{
					if(cal(map)>=score)
						return 1;
					else
						return 0;
				}
				stuckcut=1;
				return win_lose(level+1,score,map,MIN);
			}
			return 0;
		}
		else
		{
			flag=0;
			for(i=0;i<BOARD;i++)
			{
				for(j=0;j<BOARD;j++)
				{
					if(map[i][j]==NONE&&check(map,WHITE,i,j)==1)
					{
						stuckcut=0;
						memmove(tmp,map,sizeof(char)*BOARD*BOARD);
						cover(tmp,i,j,WHITE);
						if(win_lose(level+ODD,score,tmp,MAX)==0)
							return 0;
						flag=1;
					}
				}
			}
			if(flag==0)
			{
				if(stuckcut==1)
				{
					if(cal(map)>=score)
						return 1;
					else
						return 0;
				}
				stuckcut=1;
				return win_lose(level+1,score,map,MAX);
			}
			return 1;
		}
	}
}

int BS(char map[BOARD][BOARD])
{
	int i,j,num=0;
	for(i=0;i<BOARD;i++)
	{
		for(j=0;j<BOARD;j++)
		{
			if(map[i][j]==BLACK || map[i][j]==WHITE)
				num++;
		}
	}
	if(num>=BOARD*BOARD*FinalCondition1)
	{
		if(num>=BOARD*BOARD-(AI+FinalCondition2))
			Final=2;
		else
			Final=1;
	}
	else
		Final=0;
	int lb=-32768, ub=32767; //bounds for binary search
	if(Final==2)
	{
		if(win_lose(0, 0, map, MAX)==1)
		{
			lb=0;
			for(i=8;1;i+=8)
			{
				if(win_lose(0,i,map,MAX)==0)
					break;
				lb=i;
			}
			ub=i;
		}
		else
		{
			ub=0;
			for(i=-8;1;i-=8)
			{
				if(win_lose(0,i,map,MAX)==1)
					break;
				ub=i;
			}
			lb=i;
		}
	}
	else
	{
		if(win_lose(0, result, map, MAX)==1)
		{
			lb=result;
			for(i=1<<BSD;1;i<<=1)
			{
				if(win_lose(0,i+result,map,MAX)==0)
					break;
				lb=i+result;
			}
			ub=i+result;
		}
		else
		{
			ub=result;
			for(i=-1<<BSD;1;i<<=1)
			{
				if(win_lose(0,i+result,map,MAX)==1)
					break;
				ub=i+result;
			}
			lb=i+result;
		}
	}
	for(i=(ub+lb)/2;ub-lb>1;i=(ub+lb)/2)
	{
		if(win_lose(0,i, map, MAX)==1)
			lb=i;
		else
			ub=i;
	}
	return lb;
}

char savemap[BOARD][BOARD];
int firststep;

void saveboard(char map[BOARD][BOARD])
{
	memmove(savemap,map,sizeof(char)*BOARD*BOARD);
	firststep=0;
}

void restoreboard(char map[BOARD][BOARD])
{
	if(firststep==0)
		memmove(map,savemap,sizeof(char)*BOARD*BOARD);
}

void main()
{
	srand(time(0));
	//+
#ifdef _MSC_VER
	consoleinit();
#endif
	int i,j;
	bool start=0;
	bool now=0;
	bool flag=0;
	char map[BOARD][BOARD];
	bool last=0;
	char tmp[10];
	int cnum=0,ynum=0;
	FILE *out;
	char address[20];
	int rr;
	bool restart;
	int temp;
	time_t t;
	clock_t c;
	clock_t timesum;
	while(1)
	{
/* + */	strcpy(address,"record_        .txt");
//-		address[0]='r',address[1]='e',address[2]='c',address[3]='o',address[4]='r',address[5]='d',address[6]='_';
		for(i=7;i<15;i++)
		{
			address[i]=rand()%36;
			if(address[i]<10)
				address[i]+=48;
			else
				address[i]+=55;
		}
//-		address[15]='.',address[16]='t',address[17]='x',address[18]='t',address[19]=0;
		out=fopen(address,"w");
		t=time(0);
		fprintf(out,"AI v3.0 by KSHSVC, ");
		fprintf(out,ctime(&t));
		fprintf(out,"\n");
		timesum=0;
		restart=false;

		//-		printf("Who start?(0 for you,1 for computer):");
/* + */	do
/* + */	{
/* + */		printf("誰先？(0你先，1電腦先):");
			scanf("%d",&start);
/* + */	} while(start!=0 && start!=1);
		now=start;
//-		printf("Please Choose an AI(1~64,more than 7 will be slow):");
/*
		do
		 {
			printf("選擇電腦AI等級(1~64，選擇大於7的值遊戲會變慢)：");
			scanf("%d",&AI);
		} while(AI<1 || AI>64);
*/
		do
		{
			printf("Choose AI level(1.Beginner 2.Normal 3.Advanced 4.Master)：");
			scanf("%d",&AI);
		}while(AI<1 || AI>4);
		if(AI==1)
			AI=4;
		else
			AI+=4;
		fprintf(out,"AI level=%d\n",AI);
		if(start==BLACK)
			fprintf(out,"BLACK           WHITE   \n");
		else
			fprintf(out,"WHITE   BLACK           \n");
		gets(tmp);
		printf("you are O,computer is X\n");
		printf("Initial Chess Board....\n");
		for(i=0;i<BOARD;i++)
			for(j=0;j<BOARD;j++)
				map[i][j]=NONE;
		map[BOARD/2-1][BOARD/2-1]=(now!=BLACK);
		map[BOARD/2][BOARD/2]=(now!=BLACK);
		map[BOARD/2-1][BOARD/2]=(now!=WHITE);
		map[BOARD/2][BOARD/2-1]=(now!=WHITE);
		returnpos(start);
		cnum=ynum=0;
		result=0;
		paintboard(map,cnum,ynum,now);
		firststep=1;
		while(1)
		{
			flag=0;
			for(i=0;i<BOARD;i++)
			{
				for(j=0;j<BOARD;j++)
				{
					if(map[i][j]==NONE&&check(map,now,i,j)==1)
					{
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
			if(flag==0)
			{
				if(now==BLACK)
/* + */			{
/* + */				locate(9,5); myPuts("我不能下");
					lastx=lasty=-1;
//-					printf("Computer Can't Move!!\n");
/* + */			}
				if(now==WHITE)
/* + */			{
/* + */				locate(9,5); myPuts("你不能下");
//-					printf("You Can't Move!!\n");
/* + */			}
				fprintf(out,"        ");
				if(now==BLACK)
					fprintf(out,"        ");
				if(now!=start)
					fprintf(out,"\n");
/* + */			locate(11,5); myPuts("請按任意鍵繼續");
				if(now==BLACK)
					PressAnyKey();
				else //now==WHITE
				{
					if(PressAnyKeyA(26))	//check Ctrl-Z
					{
						restoreboard(map);
						cnum=ynum=0;
						paintboard(map,cnum,ynum,now);
						continue;
					}
				}
/* + */			cnum=ynum=0;
/* + */			paintboard(map,cnum,ynum,!now);
//-				printf("Press Enter to Continue.....");
//-				gets(tmp);
				if(last==0)
				{
					last=1;
					now=!now;
					continue;
				}
				else if(last==1)
					break;
			}
			if(flag==1)
				last=0;
			if(now==BLACK)
			{
				c=clock();
				result=BS(map);
				c=clock()-c;
				timesum+=c;
				lastx=bestx, lasty=besty;
//-				printf("After computer's move:\n");
				now=WHITE;
			}
			else if(now==WHITE)
			{
				while(1)
				{
//-					printf("Please Enter the place you want to put your chess(Y X):");
//-					scanf("%d %d",&bestx,&besty);
//-					gets(tmp);
					if((rr=getInput(bestx,besty))==-1)
					{
						fclose(out);
						remove(address);
						return;
					}
					if(rr==2)
					{
						restoreboard(map);
						cnum=ynum=0;
						paintboard(map,cnum,ynum,now);
						continue;
					}
					else if(rr==3)
					{
							restart=true;
							fclose(out);
							break;
					}
					else
						saveboard(map);
					if(bestx<BOARD&&besty<BOARD&&map[bestx][besty]==NONE&&check(map,WHITE,bestx,besty)==1)
					{
						break;
					}
					else
					{
/* + */					locate(20,30);
/* # */					myPuts("Illegal Move!!\n");
					}
				}
//-				if(wrong==6)
//-					break;
//-				printf("After your move:\n");
				if(restart) break;
				now=BLACK;
			}
			if(!now==BLACK)
			{
				temp=result;
				if(temp<0)
					temp=temp*-10;
				if(temp==0)
					temp=1;
				for(i=0;temp>0;i++)
					temp/=10;
				if(c>10000)
					i++;
				if(Final==2)
				{
					i++;
					fprintf(out," %d %d  *%d %.1f",bestx,besty,result,(double)c/(double)CLOCKS_PER_SEC);
				}
				else
					fprintf(out," %d %d  %d %.1f",bestx,besty,result,(double)c/(double)CLOCKS_PER_SEC);
				for(i=6-i;i>0;i--)
					fprintf(out," ");
			}
			else
				fprintf(out," %d %d    ",bestx,besty);
			if(now==start)
				fprintf(out,"\n");
			cover(map,bestx,besty,!now);
			bestx=-1;
			besty=-1;
			cnum=ynum=0;
			paintboard(map,cnum,ynum,now);
			if(!now==BLACK)
			{
				locate(19,30);
			}
		}
//-		if(wrong==6)
//-			break;
//-		printf("Final Board:\n");
		if(restart) {cls(); continue;}
		cnum=ynum=0;
		paintboard(map,cnum,ynum,now);
		if(ynum>cnum)
		{
//-			printf("You Win!!\n");
/* + */		locate(7,60); myPuts("你嬴了！");
			fprintf(out,"%d-%d, You Win!!\n",ynum,cnum);
		}
		else if(ynum==cnum)
		{
//-			printf("Draw\n");
/* + */		locate(7,60); myPuts("平手！");
			fprintf(out,"%d-%d, Draw\n",ynum,cnum);
		}
		else if(ynum<cnum)
		{
//-			printf("Computer Win!!\n");
/* + */		locate(7,60); myPuts("電腦嬴了！");
			fprintf(out,"%d-%d, Computer Win!!\n",ynum,cnum);
		}
//-		printf("Next Game?(Y/n):");
/* + */	locate(20,30); myPuts("要再來一局嗎？(Y/n):");
		gets(tmp);
		fprintf(out,"\nTotal thinking time:%.1f seconds\n",(double)timesum/(double)CLOCKS_PER_SEC);
		if(tmp[0]=='n')
			break;
		fclose(out);
	}
}
