cmp(a,b)
{
    if(!a && !b)return 0;
    if(a%10!=b%10)
        return a%10-b%10;
    return cmp(a/10,b/10);
}
numcmp(const void *a,const void *b){return cmp(*(int *)a,*(int *)b);}
main()
{
    int i,j,k,n,s[10001];
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    qsort(s,n,sizeof(s[0]),numcmp);
    for(i=0;i<n;i++)
        printf("%d%c",s[i],(i==n-1)?'\n':' ');
}
