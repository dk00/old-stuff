#include<cstdio>
inline char tonum(char &x)
{
    if(x=='A')return 1;
    if(x=='T' || x=='J' || x=='Q' || x=='K')return 10;
    return x-'0';
}
int sc(int a,int b)
{
    if(a==1 || b==1)return a+b+10;
    return a+b;
}
int u[128],s[2],d[2];
main()
{
    int i,j,k,n,C=0;
    char tmp[99];
    while(scanf("%d",&n) && n)
    {
        for(j=0;j<13;j++)u[j]=0;
        for(i=0;i<n;i++)
        {
            for(j=1;j<=10;j++)
                u[j]+=4;
            u[10]+=12;
        }
        scanf("%s",tmp);
        d[0]=tonum(tmp[0]);
        scanf("%s",tmp);
        s[0]=tonum(tmp[0]);
        scanf("%s",tmp);
        s[1]=tonum(tmp[0]);
        u[d[0]]--;
        u[s[0]]--;
        u[s[1]]--;
        j=sc(s[0],s[1]);
        for(i=1,k=0;i<=10;i++)
            if(sc(d[0],i)<j)k+=u[i];
        if(C++)puts("");
        printf("%.3lf%%\n",100.0*k/(n*52-3));
    }
}
