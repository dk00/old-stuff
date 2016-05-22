#include<cstdio>
int s[1000],t[1000];
main()
{
    long long i,j,k,l,p,q;
    int n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=k=0;i<n;i++)scanf("%d",&s[i]),k+=s[i];
        for(j=s[n-1];j<=k;)
        {
            l=(j+k)/2;
            for(i=n-1,p=0,q=1;i>=0;i--)
            {
                if(p+s[i]>l || i+q+1==m)
                    p=s[i],t[i]=1,q++;
                else
                    p+=s[i],t[i]=0;
            }
            if(j==k)break;
            if(q>m)j=l+1;
            else k=l;
        }
        for(i=0;i<n-1;i++)
        {
            printf("%d ",s[i]);
            if(t[i])printf("/ ");
        }
        printf("%d\n",s[n-1]);
    }
}
