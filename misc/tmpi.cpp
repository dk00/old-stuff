#include<cstdio>
struct pt
{
    int p,c;
    bool operator<(pt a)const{return c<a.c;}
};
int n,m,s[12],u[5],p[12],c[3][12];
int go()
{
    int i,j,k;
    for(i=0;i<n;i++)
        t[i]=(pt){p[i],c[p[i]][i]};
    sort(t,t+n);

}
void go(int i)
{
    if(i>=n)
    {
        m>?=go();
        return;
    }
    int j;
    for(j=0;j<3;j++)
        if(u[j])
        {
            u[j]--;
            p[i]=j;
            go(i+1);
            u[j]++;
        }
}
main()
{
    int i,j;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<3;i++)
            for(j=0;j<n;j++)
                scanf("%s",&c[i][j]);
        u[0]=u[1]=u[2]=n-n/2;
        go(0);
        printf("%d\n",m);
    }
}
