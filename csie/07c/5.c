n,m,t,p[100001],s[100001],u[100001];
go(int d,int i)
{
    if(d==t)
    {
        for(d=0;d<t-1;d++)
            printf("%d ",p[d]);
        printf("%d\n",p[d]);
        return;
    }
    if(i==n)return;
    if(u[s[i]%m])
    {
        p[d]=s[i];
        u[s[i]%m]--;
        go(d+1,i+1);
        u[s[i]%m]++;
    }
    go(d,i+1);
}
main()
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",s+i);
        for(j=i-1;j>=0;j--)
            if(s[j+1]<s[j])
                m=s[j+1],s[j+1]=s[j],s[j]=m;
    }
    scanf("%d",&m);
    for(i=t=0;i<m;i++)
        scanf("%d",u+i),t+=u[i];
    if(t && t<=n)go(0,0);
}
