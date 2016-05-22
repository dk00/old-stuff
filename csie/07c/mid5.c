cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
n,s[10],u[10],p[10];
go(d)
{
    if(d==n)
    {
        for(d=0;d<n;d++)
            printf("%d%c",p[d],(d==n-1)?'\n':' ');
        return;
    }
    int i;
    for(i=0;i<n;i++)
        if(!u[i])
        {
            u[i]=1;
            p[d]=s[i];
            go(d+1);
            u[i]=0;
        }
}
main()
{
    int i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    qsort(s,n,sizeof(s[0]),cmp);
    go(0);
}
