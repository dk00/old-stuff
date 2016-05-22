#include<cstdio>
#include<cstring>
main()
{
    int i,j,k,n,t,max,C=1,s[10001];
    while(scanf("%d",&n) && n)
    {
        max=0;
        memset(s,0,sizeof(s));
        for(t=0;t<n;t++)
        {
            scanf("%d %d %d",&i,&j,&k);
            max>?=i;
            for(k-=j,j=0;i<10000;i+=k)
                s[i]++;
        }
        printf("Case #%d:\n",C++);
        for(j=max;j<=10000 && s[j]!=n;j++);
        if(j<=10000)
            printf("The actual year is %d.\n",j);
        else puts("Unknown bugs detected.");
        puts("");
    }
}
