/*
PROB:paint2
LANG:C++
*/
#include<cstdio>
const int dx[]={-1,-1,-1,0,1,1,1,0},dy[]={-1,0,1,1,1,0,-1,-1};
int n,map[100][100];
char valid(int x,int y)
{
    return(x>=0 && x<n && y>=0 && y<n);
}
main()
{
    freopen("paint2.in","r",stdin);
    freopen("paint2.out","w",stdout);
    int i,j,k,l,p,sum,m;
    scanf("%d %d",&n,&m);
    for(k=0;k<m;k++)
    {
        scanf("%d %d",&i,&j);
        map[i-1][j-1]++;
    }
    for(i=sum=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            for(k=p=0;k<4;k++)
            {
                for(l=-n;l<n;l++)
                    if(l && valid(i+dx[k]*l,j+dy[k]*l))
                        p+=map[i+dx[k]*l][j+dy[k]*l];
            }
            if(p+map[i][j]==m)sum++;
        }
    printf("%d\n",sum);
}

