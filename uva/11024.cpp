#include<cstdio>
int gcd(int a,int b)
{
    while((a%=b) && (b%=a));
    return a+b;
}
main()
{
    int t,p,s1,s2,s3,s4,p1,p2,p3,p4,a1,a2,b1,b2;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d %d %d",&s1,&s2,&p1,&p2);
        scanf("%d %d %d %d",&s3,&s4,&p3,&p4);
        p=gcd(p1,gcd(p2,gcd(p3,p4)));
        for(a1=0;a1<p;a1++)
        {
            b1=p-(s1+a1)%p;
            a2=p-(s2+b1)%p;
            b2=p-(s3+a1)%p;
            if((s4+a2+b2)%p==0)
                break;
        }
        if(a1<p)puts("Yes");
        else puts("No");
    }
}
