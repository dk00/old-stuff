#include<cstdio>
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1},inf=21474836;
int n,m,d[4][99][99];
char map[99][99];
struct pt{int d,x,y;} q1[40000],q2[40000];
void bfs(int sx,int sy)
{
	int i,j,k,l,p,q,nx,ny;
	for(k=0;k<4;k++)
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			d[k][i][j]=inf;
	d[0][sx][sy]=d[1][sx][sy]=d[2][sx][sy]=d[3][sx][sy]=0;
	q1[0]=(pt){0,sx,sy};
	q1[1]=(pt){1,sx,sy};
	q1[2]=(pt){2,sx,sy};
	q1[3]=(pt){3,sx,sy};
	for(i=p=q=0,j=4;i<j || p<q;)
	{
		if(i<j)sx=q1[i].x,sy=q1[i].y,k=q1[i++].d;
		else sx=q2[p].x,sy=q2[p].y,k=q2[p++].d;
		nx=sx+dx[k];
		ny=sy+dy[k];
		if(d[k][sx][sy]<d[k][nx][ny])
		{
			d[k][nx][ny]=d[k][sx][sy];
			if(map[nx][ny]==' ')
				q1[j++]=(pt){k,nx,ny};
		}
		for(l=0;l<4;l++)
			if(l!=k && d[k][sx][sy]+1<d[l][sx][sy])
			{
				d[l][sx][sy]=d[k][sx][sy]+1;
				q2[q++]=(pt){l,sx,sy};
			}
	}
}
main()
{
	int i,j,k,l,C=1;
	while(scanf("%d %d%c",&m,&n,map[0])==3 && m+n)
	{
		n+=4;
		m+=4;
		for(i=1;i<n-1;i++)
			for(j=1;j<m-1;j++)
				map[i][j]=' ';
		for(i=0;i<n;i++)
			map[i][0]=map[i][m-1]='X';
		for(i=0;i<m;i++)
			map[0][i]=map[n-1][i]='X';
		for(i=2;i<n-2;i++)
			gets(map[i]+2);
		for(i=2;i<n-2;i++)
			map[i][m-2]=' ';
		printf("Board #%d:\n",C++);
		int P=1;
		while(scanf("%d %d %d %d",&j,&i,&l,&k) && i+j+k+l)
		{
			i++,j++,k++,l++;
			printf("Pair %d: ",P++);
			bfs(i,j);
			for(i=0,j=inf;i<4;i++)
				j=(j<d[i][k][l])?j:d[i][k][l];
			if(j>=inf)
				puts("impossible.");
			else
				printf("%d segments.\n",j+1);
		}
		puts("");
	}
}
