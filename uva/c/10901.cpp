#include<cstdio>
const int inf=2147483647;
int s1[10000],s2[10000],t1[10000],t2[10000];
main()
{
    int i,j,k,l,p,n,m,t,T,C=0;
    char tmp[1000];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&t,&m);
        for(i=j=0;m--;)
        {
            scanf("%d %s",&k,tmp);
            if(tmp[0]=='l')s1[i++]=k;
            else s2[j++]=k;
        }
        s1[i]=s2[j]=inf;
        if(C++)puts("");
        for(i=j=k=p=0;s1[i]<inf || s2[j]<inf;p=!p,k+=t)
        {
            if(k<s1[i] && k<s2[j])
                k>?=(s1[i]<?s2[j]);
            if(p)
                for(l=n;l>0 && s2[j]<inf && s2[j]<=k;l--)
                    t2[j++]=k+t;
            else
                for(l=n;l>0 && s1[i]<inf && s1[i]<=k;l--)
                    t1[i++]=k+t;
        }
        for(i=j=0;s1[i]<inf || s2[j]<inf;)
            if(s1[i]<inf && s1[i]<s2[j])
                printf("%d\n",t1[i++]);
            else
                printf("%d\n",t2[j++]);
    }
}
