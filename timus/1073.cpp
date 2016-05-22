#include<cstdio>
int s[250],t[60001];
main()
{
    int i,j,n;
    for(j=0;j<250;j++)
        s[j]=j*j;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)
            for(j=1;i+s[j]<=n;j++)
                if(!t[i+s[j]] || t[i]+1<t[i+s[j]])
                    t[i+s[j]]=t[i]+1;
        printf("%d\n",t[n]);
    }
}
