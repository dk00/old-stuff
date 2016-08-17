#include<cstdio>
int s[201];
main()
{
    char tmp[1000];
    int i,j,k,n,t,now,last;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%c",&n,tmp);
        last=0;
        for(i=0;i<=200;i++)
            s[i]=-1;
        s[100]=0;
        while(gets(tmp) && sscanf(tmp,"%d %d",&now,&k)==2)
        {
            j=now-last;
            for(i=0;i+j<=200;i++)s[i]=s[i+j];
            for(;i<=200;i++)s[i]=-1;
            for(i=1;i<=200;i++)
                if(s[i-1]>=0 && (s[i]==-1 || s[i-1]+k<s[i]))
                    s[i]=s[i-1]+k;
            last=now;
        }
        j=n-last;
        for(i=0;i+j<=200;i++)s[i]=s[i+j];
        for(;i<=200;i++)s[i]=-1;
        if(s[100]<0)
            puts("Impossible");
        else
            printf("%d\n",s[100]);
        if(t)puts("");
    }
}
