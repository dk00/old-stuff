#include<cstdio>
int n,m;
char s[10][10];
short c[10],r[10],d1[20],d2[20];
char valid(char i,char j)
{
    return c[j]+r[i]+d1[i+j]+d2[i-j+m-1]==0;
}
char test()
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(s[i][j] && valid(i,j))return 0;
    return 1;
}
int count()
{
    int i,j,k=0;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(s[i][j] && valid(i,j))k++;
    return k;
}
char go(int k,int x)
{
    if(!k || x>=n)return test();
    if(k+x>n || x>=n)return 0;
    char tmp;
    for(int i=0;i<m;i++)
        if(valid(x,i))
        {
            r[x]++,c[i]++,d1[x+i]++,d2[x-i+m-1]++;
            tmp=go(k-1,x+1);
            r[x]--,c[i]--,d1[x+i]--,d2[x-i+m-1]--;
            if(tmp)return 1;
        }
    return go(k,x+1);
}
char go(int k,int x,int i)
{
    if(i>=m)return go(k,x+1,0);
    if(!k || x>=n)return test();
    if(k+x>n || x>=n)return 0;
    char tmp;
    if(go(k,x,i+1))return 1;
    r[x]++,c[i]++,d1[x+i]++,d2[x-i+m-1]++;
    tmp=go(k-1,x,i+1);
    r[x]--,c[i]--,d1[x+i]--,d2[x-i+m-1]--;
    if(tmp)return 1;
    return 0;
}
main()
{
    int i,j,C=1;
    while(scanf("%d %d",&n,&m)==2 && n)
    {
        for(i=0;i<n;i++)
        {
            scanf("%s",s+i);
            for(j=0;s[i][j];j++)
                s[i][j]=(s[i][j]=='X');
        }
        for(i=0;!go(i,0);i++);
        for(j=1;j<i && !go(j,0,0);j++);
        printf("Case %d: %d\n",C++,j);
    }
}
