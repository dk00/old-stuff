#include<cstdio>
#include<cstdlib>
int tmp[65536];
void add(int n,char ans[])
{
    for(int i=0;i<16;i++)
        if(ans[15-i]-'0'!=((n&(1<<i))>0))
            ans[15-i]='?';
}
void print(char t0[],int n)
{
    for(int i=0;i<16;i++)
        t0[15-i]=((n&(1<<i))>0)+'0';
    t0[16]=0;
}
main()
{
    int a,b,c,s,u=0;
    char t0[99],ans[99];
    while(scanf("%d %d %d %d",&a,&b,&c,&s)==4 && a)
    {
        print(ans,s);
        for(u++;tmp[s]!=u;s=(a*s+b)%c)
        {
            tmp[s]=u;
            add(s,ans);
//            printf("%016s\n",itoa(s,t0,2));
        }
        puts(ans);
    }
}
