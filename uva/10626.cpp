#include<cstdio>
int u,n,all,s[151][151][51];
char xx[151][151][51];
int go(int c,int f,int t)
{
    if(c>=n)return 0;
    int &s1=s[c][f][t],o=all-8*c-5*f-10*t;
    if(xx[c][f][t]==u)return s1;
    xx[c][f][t]=u,s1=2000000000;
    if(t>0 && o>2)s1<?=4+go(c+1,f+1,t-1);
    if(t>0)s1<?=1+go(c+1,f,t-1);
    if(f>1)s1<?=2+go(c+1,f-2,t);
    if(f>0 && o>2)s1<?=4+go(c+1,f-1,t);
    if(o>7)s1<?=8+go(c+1,f,t);
    return s1;
}
main()
{
    int a,b,c,T;
    scanf("%d",&T);
    while(u++,T--)
    {
        scanf("%d %d %d %d",&n,&a,&b,&c);
        all=a+b*5+c*10;
        printf("%d\n",go(0,b,c));
    }
}
