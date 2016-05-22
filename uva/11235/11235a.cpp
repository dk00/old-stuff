#include<cstdio>
#include<cstring>
int num[200007],s[100001];
main()
{
    int i,j,k,n,m;
    while(scanf("%d %d",&n,&m)==2 && n)
    {
        
        for(i=0;i<n;i++)
        {
            scanf("%d",s+i);
            s[i]+=100000;
        }
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            memset(num,0,sizeof(num));
            for(k=0;i<=j;i++)
                k>?=++num[s[i]];
            printf("%d\n",k);
        }
    }
}
