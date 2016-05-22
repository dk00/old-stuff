#include<cstdio>
char x[][4]=
{
{1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
{2,1,3,4},
void mark(char v,char cl)
{
    int sum=0;
    u[v]=cl;
    for(char i=v+1;i<n;i++)
        if(c[v][i])p[i][cl]++;
    
}
void undo(char v)
{
    for(char i=0;i<n;i++)
        if(c[v][i])p[i][u[v]]--;
    u[v]=0;
}
void go(char v)
{
    int num=test(v);
    if(num<0)return;
    max>?=num;
    if(v>=n)return;
    if(u[v])go(v+1);
    for(char i=0;i<4;i++)
        if(!p[v][i])
        {
            mark(v,i);
            go(v+1);
            undo(v);
        }
}
main()
{
    while(scanf("%d %d %d %d %d %d",&n,&m,C+1,C+2,C+3,C+4)==6 && n)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        max=0;
        for(i=0;i<n;i++)
            u[i]=p[i][1]=p[i][2]=p[i][3]=p[i][4]=0;
        mark(0,1);
        for(j=1;j<n;j++)
            if(c[0][j])break;
        mark(j,2);
        go(1);
        printf("%d\n",max);
    }
}
