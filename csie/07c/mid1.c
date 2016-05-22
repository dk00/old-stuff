mod(a,b){return ((a%b)+b)%b;}
max[1001],min[1001],sum[1001];
main()
{
    int i,j,n,m;
    scanf("%d %d",&n,&m);
    for(i=0;i<m;i++)
        max[i]=0,min[i]=20000,sum[i]=0;
    for(i=0;i<n;i++)
    {
        scanf("%d",&j);
        if(j>max[mod(j,m)])
            max[mod(j,m)]=j;
        if(j<min[mod(j,m)])
            min[mod(j,m)]=j;
        sum[mod(j,m)]+=j;
    }
    for(i=0;i<m;i++)
        printf("%d %d %d\n",sum[i],max[i],min[i]);
}
