num[]={0,10,100,1000,10000,100000,1000000};
cmp(int a[],int b[])
{
    int i,j,sum=0;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            if(a[i]==b[j])sum++;
    return sum;
}
s[1000][9],t[9];
main()
{
    int i,j,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<6;j++)
            scanf("%d",&s[i][j]);
    for(j=0;j<6;j++)
        scanf("%d",&t[j]);
    for(i=j=0;i<n;i++)
        j+=num[cmp(s[i],t)];
    printf("Wow! I've won %d dollars.\n",j);
}
