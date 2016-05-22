int s1[999][999],s2[999][999],s3[999][999];
main()
{
    int i,j,n,tmp,max;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&s1[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&s2[i][j]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&s3[i][j]);
    max=0;
    for(i=0;i<n;i++)
        for(j=n-i-1;j<n;j++)
        {
            tmp=s1[i][j]+s2[i][j+i-n+1]+s3[n-j-1][i+j-n+1];
            if(tmp>max)max=tmp;
        }
    printf("%d\n",max);
}
