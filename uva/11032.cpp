#include<cstdio>
char psod[10000001];
int n,pfun[1000000];
int calcsod()
{
    int i,j,sum=0;
    for(i=0;i<=10000000;i+=10)
    {
        sum=psod[i/10];
        for(j=0;j<10;j++)
            psod[i+j]=sum++;
    }
}
inline int sod(int u){return psod[u];}
int fun(int a)
{
    int i,uu=a;
    for(i=0;a>0;a/=10,i+=9);
    i<?=uu;
    while(i--)
        if(psod[uu-i]==i)
            return uu-i;
    return -1;
}
int fun(int a,int b)
{
    int i,j,st,ed,ans=0;
    a--;
    for(st=0,ed=n-2;st<=ed;)
    {
        j=(st+ed)/2;
        if(pfun[j]<=a && a<pfun[j+1])
            break;
        if(pfun[j]>a)ed=j-1;
        else st=j+1;
    }
    ans-=j;
    for(st=0,ed=n-2;st<=ed;)
    {
        j=(st+ed)/2;
        if(pfun[j]<=b && b<pfun[j+1])
            break;
        if(pfun[j]>b)ed=j-1;
        else st=j+1;
    }
    ans+=j;
    return ans;
}
main()
{
    int i,j,t,C=1;
    char s[1000];
    calcsod();  //977786
    for(i=n=0;i<9;i++)
        if(fun(i)==-1)
            pfun[n++]=i;
    for(;i<=10000015;i++)
        if(fun(i)==-1)
        {
            for(j=0;j<100;j+=11)
            {
                if(fun(i+j)!=-1)
                    break;
                pfun[n++]=i+j;
            }
            i+=j-11;
        }
    scanf("%d%c",&t,s);
    while(t--)
    {
        gets(s);
        printf("Case %d: ",C++);
        if(sscanf(s,"%d %d",&i,&j)==1)
            printf("%d\n",fun(i));
        else printf("%d\n",fun(i,j));
    }
}
