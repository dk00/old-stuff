#include<cstdio>
const int inf=2147483647,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct pt
{
	int x,y;
}q[1100001];
int n,m,sx,sy,ex,ey,d[1005][1005],map[1005][1005];
char valid(int nx,int ny)
{
	return (nx>=0 && nx<n && ny>=0 && ny<m);
}
char sp(int l)
{
	if(map[sx][sy]<l)return 0;
	int i,j,k;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			d[i][j]=inf;
	q[0]=(pt){sx,sy};
	d[sx][sy]=0;
	for(i=0,j=1;d[ex][ey]>=inf && i<j;i++)
	{
		for(k=0;k<4;k++)
		{
			int nx=q[i].x+dx[k],ny=q[i].y+dy[k],nd=d[q[i].x][q[i].y]+1;
			if(valid(nx,ny) && map[nx][ny]>=l && nd<d[nx][ny])
				d[nx][ny]=nd,q[j++]=(pt){nx,ny};
		}
	}
	return d[ex][ey]<inf;
}
main()
{
	int i,j,k,l,x,T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d %d",&l,&n,&m);
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				map[i][j]=inf;
		scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
		for(j=0;l--;)
		{
			scanf("%d %d",&i,&k);
			map[i][k]=0;
			q[j++]=(pt){i,k};
		}
		for(i=0;i<j;i++)
			for(k=0;k<4;k++)
			{
				int nx=q[i].x+dx[k],ny=q[i].y+dy[k],nd=map[q[i].x][q[i].y]+1;
				if(valid(nx,ny) && nd<map[nx][ny])
					map[nx][ny]=nd,q[j++]=(pt){nx,ny};
			}
		for(i=0,j=l=2000;i<=j;)
		{
			k=(i+j)/2;
			if(sp(k))l=k,x=d[ex][ey],i=k+1;
			else j=k-1;
		}
		printf("%d %d\n",l,x);
	}
}
