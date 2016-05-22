#include<cstdio>
main()
{
    int i,j,k,l,n,max,C=1,c[80],p[80],s[512];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<512;i++)s[i]=-1;
        max=-1;
        for(i=0;i<n;i++)
        {
            scanf("%d %d %d %d",&j,&k,&l,c+i);
            j--,k--,l--;
            p[i]=(1<<j)|(1<<k)|(1<<l);
            if(s[511^p[i]]>=0)
                max>?=c[i]+s[511^p[i]];
            for(j=0;j<i;j++)
                if((p[i]&p[j])==0)
                    s[p[i]|p[j]]>?=c[i]+c[j];
        }
        printf("Case %d: %d\n",C++,max);
    }
}
