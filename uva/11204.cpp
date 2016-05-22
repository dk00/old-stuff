#include<cstdio>
main()
{
    int i,j,n,m,T,s[32];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)s[i]=0;
        while(m--)
        {
            for(i=0;i<n;i++)
            {
                scanf("%d",&j);
                if(j==1)s[i]++;
            }
        }
        for(i=0,j=1;i<n;i++)
            if(s[i])j*=s[i];
        printf("%d\n",j);
    }
}
