#include<cstdio>
int s[10000];
main()
{
    int i,j,n;
    while(scanf("%d:",&n) && n)
    {
        for(j=0;j<n;j++)
            scanf("%d",&i),s[i]=j;
        for(i=0;i<n;i++)
        {
            for(j=1;i+j+j<n;j++)
                if((s[i]-s[i+j])*(s[i+j]-s[i+j+j])>0)
                    break;
            if(i+j+j<n)break;
        }
        if(i>=n)puts("yes");
        else puts("no");
    }
}
