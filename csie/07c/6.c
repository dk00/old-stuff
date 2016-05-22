typedef struct
{
    int p,q;
}frac;
gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
frac reduce(frac x)
{
    int d=gcd(x.p,x.q);
    x.p/=d;
    x.q/=d;
    return x;
}
frac add(frac a,frac b)
{
    frac c;
    c.q=a.q*b.q;
    c.p=a.p*b.q+b.p*a.q;
    return reduce(c);
}
frac mul(frac a,frac b)
{
    frac c;
    int d=gcd(a.p,b.q);
    a.p/=d,b.q/=d;
    d=gcd(b.p,a.q);
    b.p/=d,a.q/=d;
    c.p=a.p*b.p;
    c.q=a.q*b.q;
    return reduce(c);
}
frac s[20][20];
main()
{
    int i,j,l,r,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<=n;i++)
            for(j=0;j<=i;j++)
                s[i][j]=(frac){0,1};
        s[0][0]=(frac){1,1};
        for(i=0;i<n;i++)
            for(j=0;j<=i;j++)
            {
                scanf("%d %d",&l,&r);
                s[i+1][j]=add(s[i+1][j],mul(s[i][j],(frac){l,l+r}));
                s[i+1][j+1]=add(s[i+1][j+1],mul(s[i][j],(frac){r,l+r}));
            }
        for(j=0;j<=n;j++)
            printf("%d/%d\n",s[n][j].p,s[n][j].q);
    }
}
