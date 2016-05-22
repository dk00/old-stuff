#include<cstdio>
char n,c[15],d1[30],d2[30],p[15];
int count;
void go1(char r)
{
    if(count==0)return;
    if(r>=n)
    {
        for(r=0;r<n-1;r++)
            printf("%d ",p[r]+1);
        printf("%d\n",p[r]+1);
        count++;
        return;
    }
    for(char i=0;i<n;i++)
        if(c[i]+d1[i+r]+d2[i-r+n-1]==0)
        {
            c[i]++,d1[i+r]++,d2[i-r+n-1]++;
            p[r]=i,go1(r+1);
            c[i]--,d1[i+r]--,d2[i-r+n-1]--;
        }
}
void go(char r)
{
    if(r>=n)
    {
        count++;
        return;
    }
    for(register char i=0;i<n;i++)
        if(c[i]+d1[i+r]+d2[i-r+n-1]==0)
        {
            c[i]++,d1[i+r]++,d2[i-r+n-1]++;
            go(r+1);
            c[i]--,d1[i+r]--,d2[i-r+n-1]--;
        }
}
main()
{
    freopen("checker.in","r",stdin);
    freopen("checker.out","w",stdout);
    int i,r;
    scanf("%d",&n);
    count=-3;
    go1(0);
    if(n==13)
    {
        for(i=r=0;i<6;i++)
        {
            c[i]++,d1[i+r]++,d2[i-r+n-1]++;
            go(1);
            c[i]--,d1[i+r]--,d2[i-r+n-1]--;
        }
        c[i]++,d1[i+r]++,d2[i-r+n-1]++;
        for(i=0,r=1;i<6;i++)
            if(c[i]+d1[i+r]+d2[i-r+n-1]==0)
            {
                c[i]++,d1[i+r]++,d2[i-r+n-1]++;
                go(r+1);
                c[i]--,d1[i+r]--,d2[i-r+n-1]--;
            }
        count*=2;
    }
    else go(0);
    printf("%d\n",count);
    scanf(" ");
}
/*
PROB:checker
LANG:C++
*/
