#include<cstdio>
long long s[99],t[99];
main()
{
    int i,j,k,n,T;
    char tmp[99];
    scanf("%d%c",&T,tmp);
    while(T--)
    {
        s[0]=0,s[1]=s[2]=1;
        t[0]=t[1]=1,t[2]=0;
        n=3;
        gets(tmp);
        for(i=0,j=1;tmp[i];i++)
        {
            if(tmp[i]=='R')j++;
            for(k=n++;k>j;k--)
                s[k]=s[k-1],t[k]=t[k-1];
            s[j]=s[j-1]+s[j+1];
            t[j]=t[j-1]+t[j+1];
        }
        printf("%lld/%lld\n",s[j],t[j]);
    }
}
