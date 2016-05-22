#include<stdio.h>
main()
{
    int i,j,k,n,T,C=1,s[100],t[100];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<32;i++)
            s[i]=t[i]=0;
        if(n<0)j=1,n=-n;
        else j=0;
        for(k=1,i=0;k<=n;k*=2,i++)
            if(n&k)s[i]=1;
            else s[i]=0;
        for(;i<32;i++)s[i]=0;
        for(i=0;i<32;i++,j=!j)
        {
            if(j && s[i])s[i]--,t[i]++,t[i+1]++;
            else if(!j && s[i])s[i]--,t[i]++;
            while(t[i]>=2)
            {
                t[i]-=2;
                if(t[i+1])t[i+1]--;
                else t[i+1]++,t[i+2]++;
            }
        }
        printf("Case #%d: ",C++);
        for(i=31;i>0 && t[i]==0;i--);
        while(i>=0)putchar(t[i--]+'0');
        puts("");
    }
}
