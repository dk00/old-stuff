#include<cstdio>
#include "libconq.h"
int s[2001],t[2001];
main()
{
    int i,j,n;
    start(&n,s);
    while(1)
    {
        for(i=2,j=1;i<=n && j<=1000000000;i++,j*=2)
        {
            if(s[i]>=j)
            {
                t[i]=j;
                break;
            }
            j-=(t[i]=s[i]);
        }
        i=step(t);
        if(i==1)
            for(i=1;i<n;i++)
                s[i]=t[i+1],t[i+1]=0;
        else
            for(i=1;i<n;i++)
                s[i]=s[i+1]-t[i+1],t[i+1]=0;
        s[n]=0;
        while(n>0 && !s[n])n--;
    }
}
