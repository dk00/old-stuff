main()
{
    int n,T,a1,b1,a2,b2,a3,b3;
    long long i,j;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%d %d %d",&a1,&a2,&a3);
        scanf("%d %d %d",&b1,&b2,&b3);
        for(i=0;i<=a1 && i*b1<=n;i++)
            for(j=0;j<=a2 && i*b1+j*b2<=n;j++)
                if((n-i*b1-j*b2)==0)goto yes;
                else if(b3 && (n-i*b1-j*b2)%b3==0 && (n-i*b1-j*b2)/b3<=a3)
                    goto yes;
        puts("no");
        continue;
    yes:puts("yes");
    }
}
