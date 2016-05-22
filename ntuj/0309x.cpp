#include<cstdio>
const int dx[]={0,0,0,0,1,-1},dy[]={0,1,0,-1,0,0},dz[]={1,0,-1,0,0,0}
,p[][6]={{0,0,0,0,2,2},{1,2,1,2,1,1},{2,1,2,1,0,0}},
	q[][6]={{1,1,1,1,-1,1},{1,-1,-1,1,0,0},{1,1,-1-1,1,-1}};
int n;
char map[11][11][11],tmp[11][11][11];
int proc(int x)
{
	int i,j,k,l,sum=0,s[3],t[3];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(tmp[x][i][j]=='.')
				for(k=0;k<n;k++)
				{
					s[0]=i,s[1]=j,s[2]=k;
					for(l=0;l<3;l++)
					{
						t[l]=s[p[l][x]]*q[l][x];
						if(t[l]<0)t[l]+=n-1;
					}
					if(map[t[0]][t[1]][t[2]])
						map[t[0]][t[1]][t[2]]=0,sum++;			
				}
	}
	printf("%d\n",sum);
	return sum;
}
main()
{
	int i,j,k,sum;
	while(scanf("%d",&n)==1 && n)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(k=0;k<n;k++)
					map[i][j][k]=1;
		for(i=0;i<3;i++)
			for(j=0;j<6;j++)
				scanf("%s",tmp[j][i]);
		sum=n*n*n;	
		for(i=0;i<6;i++)
			sum-=proc(i);
		printf("%d\n",sum);
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				for(k=0;k<3;k++)
					printf("%d",map[i][j][k]);
				puts("");
			}
			puts("");
		}
	}
}
