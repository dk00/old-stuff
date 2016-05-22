#include<cstdio>
int exp(int n,int k)
{
    if(k==0)
        return 1;
    if(k%2)
        return n*exp(n,k-1);
    int tmp=exp(n,k/2);
    return tmp*tmp;
}
main()
{
    int i,j,k,d,q,x[100],C=1;
    char s[1000],p[1000];
    while(scanf("%d",&d) && d)
    {
        for(i=0;i<d;i++)
            scanf(" x%d",&x[i]);
        scanf("%s",s);
        scanf("%d",&q);
        printf("S-Tree #%d:\n",C++);
        while(q--)
        {
            scanf("%s",p);
            for(i=j=0,k=exp(2,d-1);i<d;i++,k>>=1)
                if(p[x[i]-1]=='1')
                    j+=k;
            printf("%c",s[j]);
        }
        puts("\n");
    }
}
