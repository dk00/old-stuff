#include<cstdio>
int s[63000],t[63000];
main()
{
    int i,j,k,l,n,p,n1,n2,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&n1,&n2);
        n*=n;
        for(i=1;i<=n;i++)s[i]=-1;
        for(i=0;i<=n1;i++)
        {
            scanf("%d",&j);
            s[j]=i;
        }
        for(i=k=0;i<=n2;i++)
        {
            scanf("%d",&j);
            if(s[j]>=0)t[k++]=s[j];
        }
        n=k;
        s[0]=t[0];
        for(i=l=1;i<n;i++)
        {
            for(j=0,k=l;j<=k;)
            {
                p=(j+k)/2;
                if((!p || s[p-1]<t[i])&&(p==l || t[i]<s[p]))
                    break;
                if(!p || s[p-1]<t[i])j=p+1;
                else k=p-1;
            }
            if(p==l)s[l++]=t[i];
            else s[p]=t[i];
        }
        printf("Case %d: %d\n",C++,l);
    }
}
