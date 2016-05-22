#include<cstdio>
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
char map[99][99];
int u[4][99][99];
int n,m;
int c[4][2][4]={
	{{1,-1,-1,1},{2,-1,-1,3}},
	{{-1,0,0,-1},{-1,2,3,-1}},
	{{-1,-1,0,1},{-1,-1,3,3}},
	{{1,0,-1,-1},{2,2,-1,-1}}};
char d[4][4]={{1,0,0,1},{0,1,1,0},{0,0,1,1},{1,1,0,0}};
int go(int d1,int z,int x,int y)
{

	if(x<0 || x>=n || y<0 || y>=m)
		return -1;
	if(u[z][x][y]==0)return 0;
	u[z][x][y]=d1;
	int k,nx,ny,tmp;
	for(k=0;k<4;k++)
	{
        if(!d[z][k])continue;
		if((nx=x+dx[k])<0 || nx>=n || (ny=y+dy[k])<0 || ny>=m)
			return -1;
		if(c[z][map[nx][ny]=='/'][k]>=0 &&
        u[c[z][map[nx][ny]=='/'][k]][nx][ny]!=d1-1 &&
        u[c[z][map[nx][ny]=='/'][k]][nx][ny]<1)
			tmp=go(d1+1,c[z][map[nx][ny]=='/'][k],nx,ny);
        else continue;
		if(tmp==-1)return -1;
		if(tmp>=0)return tmp+1;
	}
}
main()
{
	int i,j,k,num,max,C=1;
	while(scanf("%d %d",&m,&n)==2 && m+n)
	{
		for(i=num=max=0;i<n;i++)
		{
			scanf("%s",map[i]);
			for(j=0;j<m;j++)
				u[0][i][j]=u[1][i][j]=u[2][i][j]=u[3][i][j]=-2;
		}
		for(i=num=0;i<n;i++)
			for(j=0;j<m;j++)
			{
                k=-1;
                if(u[(map[i][j]=='/')*2][i][j]==-2)
                {
				    k=go(0,(map[i][j]=='/')*2,i,j);
				    if(k>0)num++;
                }
                if(u[(map[i][j]=='/')*2+1][i][j]==-2)
                {
				    k=go(0,(map[i][j]=='/')*2+1,i,j);
				    if(k>0)num++;
                }
				if(k>max)max=k;
			}
		if(num)
			printf("Maze #%d:\n%d Cycles; the longest has length %d.\n",
			C++,num,max);
		else
			printf("Maze #%d:\nThere are no cycles.\n",C++);
        puts("");
	}
}
