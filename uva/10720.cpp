#include<cstdio>
#include<algorithm>
int s[10001];
main()
{
    int i,j,n;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        if(s[n-1]>=n)
        {
            puts("Not possible");
            continue;
        }
        for(i=n-1;n && i>0;i--)
        {
            std::sort(s,s+i+1);
            if(i-s[i]<0)n=0;
            for(j=i-s[i];n && j<i;j++)
            {
                s[j]--;
                if(s[j]<0)n=0;
            }
        }
        if(!n || i || s[i])
            puts("Not possible");
        else
            puts("Possible");
    }
}
