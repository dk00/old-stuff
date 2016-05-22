#include <stdio.h>
#include <stdlib.h>

struct point
{
	long x,y;
};

int dir[8][2]={ {1,2},{1,-2},{-1,2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1} };

int used[52][52];
long n;
int solve;
point start;

int cmp(const void *a,const void *b)
{
	long *c=(long *)a;
	long *d=(long *)b;
	if(c[1]>d[1])
		return 1;
	else if(c[1]<d[1])
		return -1;
	else
	{
		if(c[2]>d[2])
			return -1;
		else if(c[2]<d[2])
			return 1;
		return 0;
	}
}

void get_seq(point x,long *a)
{
	point temp,tr;
	long i,j,b[10][3],count;
	for(i=0;i<8;i++)
	{
		b[i][0]=i;
		temp.x=x.x+dir[i][0];
		temp.y=x.y+dir[i][1];
		if(temp.x>=0 && temp.x<n && temp.y>=0 && temp.y<n)
		{
			count=0;
			for(j=0;j<8;j++)
			{
				tr.x=temp.x+dir[j][0];
				tr.y=temp.y+dir[j][1];
				if(tr.x>=0 && tr.x<n && tr.y>=0 && tr.y<n && used[tr.x][tr.y]==0)
					count++;
			}
			b[i][1]=count;
		}
		else
			b[i][1]=0;
		b[i][2]=(temp.x-(n-1)/2)*(temp.x-(n-1)/2)+(temp.y-(n-1)/2)*(temp.y-(n-1)/2);
//		b[i][2]=0;
	}
	qsort((void *)b,8,sizeof(b[0]),cmp);
	for(i=0;i<8;i++)
		a[i]=b[i][0];
}

void dfs(point x,long depth)
{
	point next;
	long a[10];
	long i,j;
	used[x.x][x.y]=depth+1;
	if(depth==n*n-1)
	{
//		if( (labs(x.x-start.x)==2 && labs(x.y-start.y)==1) ||
  //			(labs(x.x-start.x)==1 && labs(x.y-start.y)==2) )
//		{
			solve=1;
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
					printf("%5d",used[i][j]);
				printf("\n");
			}
//		}

	}
	else
	{
		get_seq(x,a);
		for(i=0;i<8;i++)
		{
			next.x=x.x+dir[a[i]][0];
			next.y=x.y+dir[a[i]][1];
			if(next.x>=0 && next.x<n && next.y>=0 && next.y<n && used[next.x][next.y]==0)
				dfs(next,depth+1);
			if(solve)
				break;
		}
	}
	used[x.x][x.y]=0;
}

int main()
{
	int in=0;
	long i,j;
//	point start;
//	int used[52][52];
//	long n;
	while(scanf("%ld",&n)==1)
	{
		if(in==1)
			printf("\n");
		in=1;
		scanf("%ld %ld",&start.x,&start.y);
		start.x--;start.y--;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				used[i][j]=0;
		}
		solve=0;
		if(n%2!=1 || n==1)
			dfs(start,0);
		if(solve==0)
			printf("No Circuit Tour.\n");
	}
	return 0;
}
