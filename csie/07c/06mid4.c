n,s[9999];
go(i,v)
{
    if(!v)return 1;
    if(i>=n || v<0)return 0;
    if(go(i+1,v-s[i]))
        return 1;
    return go(i+1,v);
}
main()
{
    int i,T,sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=sum=0;i<n;i++)
            scanf("%Id",s+i),sum+=s[i];
        if(sum%2==0 && go(0,sum/2))
            puts("yes");
        else puts("no");
    }
}
