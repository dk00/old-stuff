#include<cstdio>
char c[128][128];
main()
{
    int i,j,k,n,w[100],l[100],C=0;
    char tmp1[100],tmp2[100];
    c['p']['r']=c['r']['s']=c['s']['p']=1;
    while(scanf("%d %d",&n,&k) && n)
    {
        for(i=0;i<n;i++)w[i]=l[i]=0;
        for(k=n*(n-1)/2*k;k--;)
        {
            scanf("%d %s %d %s",&i,tmp1,&j,tmp2);
            i--,j--;
            if(c[*tmp1][*tmp2])
                w[i]++,l[j]++;
            else if(c[*tmp2][*tmp1])
                w[j]++,l[i]++;
        }
        if(C++)puts("");
        for(i=0;i<n;i++)
            if(w[i]+l[i])
                printf("%.3lf\n",1.0*w[i]/(w[i]+l[i]));
            else
                puts("-");
    }
}
