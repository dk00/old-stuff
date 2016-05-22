#include<cstdio>
#include<cstdlib>
const int N=2147483647,M=999999;
int n,s[M],t[M],l[M];
int go(int st,int ed)
{
    int i,ns,nt;
    int k=0;
    for(i=0;i<n;i++)
    {
        ns=s[i]>?((st+l[i]-s[i]%l[i]-1)/l[i]*l[i]+s[i]%l[i]);
        nt=ed<?t[i];
        if(ns<=nt)k+=(l[i]+nt-ns)/l[i];
    }
    return k;
}
main()
{
    int i,j,k;
    char tmp[99];
    while(gets(tmp))
    {
        while(!tmp[0])
            if(!gets(tmp))return 0;
        for(n=0;tmp[0];n++)
        {
            sscanf(tmp,"%d %d %d",s+n,t+n,l+n);
            if(!gets(tmp))tmp[0]=0;
        }
        if(1-go(1,N)%2)
        {
            puts("no corruption");
            continue;
        }
        for(i=1,j=N;i<j;)
        {
            k=(i+0ll+j)/2;
            if(go(i,k)%2)j=k;
            else i=k+1;
        }
        printf("%d %d\n",i,go(i,i));
    }
}
