main()
{
    int i,j,k,n,s[99],d[99];
    char tmp[99];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",tmp);
        if(tmp[0]!='*')
            d[i]=sscanf(tmp,"%d",s+i);
        else
            d[i]=0;
    }
    for(i=0;!d[i];i++);
    for(j=i+1;!d[j];j++);
    if((s[j]-s[i])%(j-i))
    {
        puts("no solution");
        continue;
    }
    k=(s[j]-s[i])/(j-i);
    j=s[i]-i*k;
    for(i=0;i<n;i++,j+=k)
    {
        if(d[i] && s[i]!=j)
            break;
        s[i]=j;
    }
    if(i<n)
    {
        puts("no solution");
        continue;
    }
    for(i=0;i<n;i++)
        printf("%d%c",s[i],i==n-1?'\n':' ');
}
