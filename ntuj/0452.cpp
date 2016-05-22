#include<cstdio>
#include<cstring>
int L,dn,*dx,*dy,*px,*py;
int _dx[][8]=
{
	{-1,0,1,0},
	{-1,1,1,-1},
	{-2,-1, 1, 2, 2, 1,-1,-2},
	{-1,-1,0,1,1,1,0,-1}
},_dy[][8]={
	{0,1,0,-1},
	{1,1,-1,-1},
	{ 1, 2, 2, 1,-1,-2,-2,-1},
	{0,1,1,1,0,-1,-1,-1}
};
int setx(int n)
{
	if(n<2)L=4;
	else L=8;
	px=_dx[n];
	py=_dy[n];
	return 1;
}
int set(int n)
{
	if(n<2)L=4;
	else L=8;
	dx=_dx[n];
	dy=_dy[n];
	return 1;
}
char map[9][9],at[9][9],tmp0[9][9];
inline char valid(int x,int y)
{
	if(x<0 || x>=8 || y<0 || y>=8)
		return 0;
	return 1;
}
inline char validx(int x,int y)
{
	if('a'<=map[x][y] && map[x][y]<='z')return 0;
	if(x<0 || x>=8 || y<0 || y>=8)
		return 0;
	return 1;
}

void go(int m,int x,int y)
{
	int i,j,nx,ny;
	for(i=0;i<L;i++)
		for(j=1;j<=m;j++)
		{
			nx=x+dx[i]*j,ny=y+dy[i]*j;
			if(!valid(nx,ny))break;
			at[nx][ny]=1;
			if(map[nx][ny]!='.')break;
		}
}
char ischeck()
{
	int i,j;
	memset(at,0,sizeof(at));
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			if(map[i][j]=='R')set(0),go(8,i,j);
			if(map[i][j]=='B')set(1),go(8,i,j);
			if(map[i][j]=='Q')set(0),go(8,i,j),set(1),go(8,i,j);
			if(map[i][j]=='N')set(2),go(1,i,j);
			if(map[i][j]=='K')set(3),go(1,i,j);
		}
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			if(map[i][j]=='k')
				return at[i][j];
	return 0;
}
void print(char s[9][9])
{
	puts("");
	for(int i=0;i<8;i++)
		puts(s[i]);
}
char test(int m,int x,int y)
{
	int *dx=px,*dy=py;
	int i,j,nx,ny,ch;
	for(i=0;i<L;i++)
		for(j=1;j<=m;j++)
		{
			memcpy(tmp0,map,sizeof(map));
			nx=x+dx[i]*j,ny=y+dy[i]*j;
			if(!validx(nx,ny))break;
			map[nx][ny]=map[x][y];
			map[x][y]='.';
			ch=ischeck();
			if(!ch)
			{
//				print(map);
			}
			memcpy(map,tmp0,sizeof(map));
			if(!ch)return 1;
			if(map[nx][ny]!='.')break;
		}
	return 0;
}
char u1[128],u2[128];
void change()
{
	int i,j;
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
			map[i][j]=u1[map[i][j]];
}
main()
{
	u1['r']='R';u1['b']='B';u1['q']='Q';u1['n']='N';u1['k']='K';
	u1['R']='r';u1['B']='b';u1['Q']='q';u1['N']='n';u1['K']='k';u1['.']='.';
	int i,j,k,l,T;
	scanf("%d",&T);
	char q[99];
	while(T--)
	{
		scanf("%s",q);
		for(i=0;i<8;i++)
			scanf("%s",map[i]);
		if(q[0]!='w')
		{
			change();
			printf("BLACK IS ");
		}
		else printf("WHITE IS ");
		l=ischeck();k=1;
		for(i=0;i<8;i++)
			for(j=0;j<8;j++)
			{
				if(map[i][j]=='r'){setx(0);if(test(8,i,j))k=0;}
				if(map[i][j]=='b'){setx(1);if(test(8,i,j))k=0;}
				if(map[i][j]=='q'){setx(0);if(test(8,i,j))k=0;
					setx(1);if(test(8,i,j))k=0;}
				if(map[i][j]=='n'){setx(2);if(test(1,i,j))k=0;}
				if(map[i][j]=='k'){setx(3);if(test(1,i,j))k=0;}
			}
		if(k) puts("CHECKMATED");
		else if(l)puts("CHECKED");
		else puts("SAFE");
	}
}
