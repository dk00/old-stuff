#include<cstdio>
#include<algorithm>
const int inf=2000000000;
int max,next,s[9][9],p[99];
int h()
{
	int i,j,k=0;
	for(i=1;i<=4;i++)
		for(j=1;j<=8;j++)
			if(s[i][j] && s[i][j]!=i*10+j)
				k++;
	return k;
}
void print()
{
	int i,j;
	for(i=1;i<=4;i++,puts(""))
		for(j=1;j<=8;j++)
			printf("%d ",p[i*10+j]);
}
char go(int d)
{
	int tmp=h();
	if(d+tmp>max)
	{
		if(d+tmp<next)next=d+tmp;
		return 0;
	}
	if(!tmp)return 1;
	int i,j,nx,ny;
	for(i=1;i<=4;i++)
		for(j=2;j<=8;j++)
			if(!s[i][j] && s[i][j-1] && s[i][j-1]%10<7)
			{
				nx=p[s[i][j-1]+1]/10;
				ny=p[s[i][j-1]+1]%10;
				std::swap(s[i][j],s[nx][ny]);
				p[s[i][j]]=i*10+j;
				tmp=go(d+1);
				std::swap(s[i][j],s[nx][ny]);
				p[s[nx][ny]]=nx*10+ny;
				if(tmp)return 1;
			}
	return 0;
}
main()
{
	int i,j,T;
	scanf("%d",&T);
	while(T--)
	{
		for(i=1;i<=4;i++)
		{
			for(j=2;j<=8;j++)
			{
				scanf("%d",s[i]+j);
				if(s[i][j]%10==1)
					s[i][j]=0;
				p[s[i][j]]=i*10+j;
			}
			s[i][1]=i*10+1;
			p[i*10+1]=i*10+1;
		}
		print();
		max=h(),next=inf;
		for(;;)
		{
			printf("%d\n",max);
			if(go(0))break;
			if(next>=inf){max=-1;break;}
			max=next,next=inf;
		}
		printf("%d\n",max);
	}
}
