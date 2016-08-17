#include<cstdio>
int s[10000];
main()
{
    int i,j,n,m,x;
    while(scanf("%d %d",&n,&m) && n)
    {
        for(i=x=0;i<10000;i++)s[i]=0;
        for(i=0;i<n;i++)
            scanf("%d",&j),s[j]++;
        while(m--)
        {
            scanf("%d %d",&n,&j);
            while(n--)
            {
                scanf("%d",&i);
                if(s[i])j--;
            }
            if(j>0)x=1;
        }
        if(x)puts("no");
        else puts("yes");
    }
}
