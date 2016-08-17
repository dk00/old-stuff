#include<cstdio>
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&k,&n);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            m=gcd(i,j);
            i/=m,j/=m;
            if(i-j==k+1 || j-i==k+1)
                puts("LOSING");
            else
                puts("WINNING");
        }
        puts("");
    }
}
