#include<cstdio>
int pr[10000];  //Prime Factor
bool notp[46341];
main()
{
    int i,j,n,pn,first;
    pr[0]=2;
    for(pn=1,i=3;i<46340;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*3;j<46340;j+=i*2)
            notp[j]=1;
        pr[pn++]=i;
    }
    while(scanf("%d",&n) && n)
    {
        first=1;
        for(i=0;n>1 && pr[i]<=n && i<pn;i++)
        {
            if(n%pr[i]==0)
            {
                if(first)first=0;
                else printf("*");
                for(j=0;n%pr[i]==0;j++)
                    n/=pr[i];
                printf("%d^%d",pr[i],j);
            }
        }
        if(n>1)
        {
            if(first)first=0;
            else printf("*");
            printf("%d^1",n);
        }
        puts("");
    }
}
