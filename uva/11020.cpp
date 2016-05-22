#include<cstdio>
int s1[15000][2],s2[15000][2];
main()
{
    freopen("11020.in","r",stdin);
    int i,j,k,l,n,m,t,C=1;
    scanf("%d",&t);
    while(t--)
    {
        n=0;
        scanf("%d",&m);
        if(C>1)puts("");
        printf("Case #%d:\n",C++);
        while(m--)
        {
            scanf("%d %d",&i,&j);
            for(k=l=0;k<n;k++)
                if(s1[k][0]<i || s1[k][1]<j ||(s1[k][0]<=i && s1[k][1]<=j))
                    s2[l][0]=s1[k][0],s2[l++][1]=s1[k][1];
            for(k=0;k<n;k++)
                if((s1[k][0]<i && s1[k][1]<=j) ||
                (s1[k][0]<=i && s1[k][1]<j))
                    break;
            if(k>=n)
                s2[l][0]=i,s2[l++][1]=j;
            for(n=0;n<l;n++)
                s1[n][0]=s2[n][0],s1[n][1]=s2[n][1];
            printf("%d ",n);
        }
        puts("");
    }
}
