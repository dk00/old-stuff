#include<cstdio>
struct x
{
    char s[15];
}s[457420],*_s;
int n,pn[20];
char path[30],c[30],l[30],r[30],map[15][15];
char fit(char *a)
{
    for(int i=0;i<n;i++)
        if(!map[i][a[i]])return 0;
    return 1;
}
char pro(int d)
{
    for(;d<n;d++)
    {
        int i;
        for(i=0;i<n;i++)
            if(map[d][i] && c[i] && l[d+i] && r[n-1+d-i])
                break;
        if(i>=n)return 1;
    }
    return 0;
}
int *_n;
void go(int d)
{
    if(d>=n)
    {
        for(int i=0;i<n;i++)
            s[*_n].s[i]=path[i];
        (*_n)++;
        return;
    }
    //if(pro(d))return 0;
    for(int i=0;i<n;i++)
        if(c[i] && l[d+i] && r[n-1+d-i])
        {
            path[d]=i;
            c[i]=l[d+i]=r[n-1+d-i]=0;
            go(d+1);
            c[i]=l[d+i]=r[n-1+d-i]=1;
        }
}
main()
{
    int i,j,C=1;
    for(i=0;i<30;i++)
        c[i]=l[i]=r[i]=1;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            map[i][j]=1;
    for(n=4;n<15;n++)
    {
        pn[n]=pn[n-1];
        _n=pn+n;
        go(0);
    }
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
        {
            scanf("%s",map[i]);
            for(j=0;map[i][j];j++)
                map[i][j]=(map[i][j]=='.');
        }
        for(j=0,i=pn[n-1];i<pn[n];i++)
            if(fit(s[i].s))j++;
        printf("Case %d: %d\n",C++,j);
    }
}
