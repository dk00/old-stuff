#include<stdio.h>
#include<stdlib.h>
int cmp(const void *a,const void *b)
{
    int a1=*(int *)a,b1=*(int *)b;
    if(a1<b1)return -1;
    if(a1==b1)return 0;
    return 1;
}
int n,m,dx[]={1,0,-1,0},dy[]={0,1,0,-1},t[50000];
char s[205][205];
int go(int x,int y)
{
    if(x<0 || x>=n || y<0 || y>=m || s[x][y]!='1')
        return 0;
    s[x][y]='0';
    int i,sum=1;
    for(i=0;i<4;i++)
        sum+=go(x+dx[i],y+dy[i]);
    return sum;
}
main()
{
    int i,j,k,l;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%s",s[i]);
    for(i=k=0;i<n;i++)
        for(j=0;j<m;j++)
            if(s[i][j]=='1')
                t[k++]=go(i,j);
    qsort(t,k,sizeof(t[0]),cmp);
    for(i=0;i<k;i++)
        printf("%d\n",t[i]);
}
