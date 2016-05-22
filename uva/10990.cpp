#include<cstdio>
char notp[2000001];
int n,p[400000],s[2000001];
void go(int num,int x,int i)
{
    if(1ll*num*p[i]<=2000000)
        go(num*p[i],x*p[i],i);
    for(i++;1ll*num*p[i]<=2000000 && i<n;i++)
        go(num*p[i],x*(p[i]-1),i);
    s[num]=x;
}
main()
{
    p[0]=2000001;
    p[1]=2;
    int i,j,T;
    for(n=2,i=3;i<2000000;i++,i++)
    {
        if(notp[i])continue;
        if(i<1500)
            for(j=i*i;j<2000000;j+=i*2)
                notp[j]=1;
        p[n++]=i;
    }
    go(1,1,0);
    s[0]=s[1]=0;
    for(i=2;i<=2000000;i++)
        s[i]=s[s[i]]+1;
    for(i=2;i<=2000000;i++)
        s[i]+=s[i-1];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&i,&j);
        printf("%d\n",s[j]-s[i-1]);
    }
}
