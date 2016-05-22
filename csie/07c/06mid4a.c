main()
{
    int i,j,n,T,sum,tmp,s[25];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=sum=0;i<n;i++)
            scanf("%d",&s[i]),sum+=s[i];
        if(sum%2)
        {
            puts("no");
            continue;
        }
        for(j=(1<<n)-1;j>0;j--)
        {
            for(i=n-1,tmp=0;tmp*2<=sum && i>=0;i--)
                if(j&(1<<i))
                    tmp+=s[i];
            if(tmp*2==sum)break;
        }
        if(j>0)puts("yes");
        else puts("no");
    }
}
