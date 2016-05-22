#include<cstdio>
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
char u[2][99][99],map[99][99];
int n,m;
int c[4][2][4]={
	{{1,-1,-1,1},{2,-1,-1,3}},
	{{-1,0,0,-1},{-1,2,3,-1}},
	{{-1,-1,0,1},{-1,-1,3,3}},
	{{1,0,-1,-1},{2,2,-1,-1}}};
int go(int z,int x,int y)
{

	if(x<0 || x>=n || y<0 || y>=n)
		return -1;
	if(!u[z%2][x][y])return 0;
	u[z%2][x][y]=0;
	int k,nx,ny,tmp;
	for(k=0;k<4;k++)
	{
		if((nx=x+dx[k])<0 || nx>=n || (ny=y+dy[k])<0 || ny>=m)
			return -1;
		if(c[z][map[nx][ny]=='/'][k]>=0)
			tmp=go(c[z][map[nx][ny]=='/'][k],nx,ny);
		if(tmp==-1)return -1;
		if(tmp>=0)return tmp+1;
	}
}
main()
{
	int i,j,k,num,max,C=1;
	while(scanf("%d %d",&m,&n)==2)
	{
		for(i=num=max=0;i<n;i++)
		{
			scanf("%s",map[i]);
			for(j=0;j<m;j++)
				u[0][i][j]=u[1][i][j]=1;
		}
		for(i=num=0;i<n;i++)
			for(j=0;j<m;j++)
			{
				k=go((map[i][j]=='/')*2,i,j);
				if(k>0)num++;
				k=go((map[i][j]=='/')*2+1,i,j);
				if(k>0)num++;
				if(k>max)max=k;
			}
		if(num)
			printf("Maze #%d:\n%d Cycles; the longest has length %d.\n",
			C++,num,max);
		else
			printf("Maze #%d:\nThere are no cycles.\n",C++);
	}
}
