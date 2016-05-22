char map[300],u[10000];
go(int n1,int n2,int a,int b)
{
    int i,j;
    char tmp1[9],tmp2[9];
    sprintf(tmp1,"%04d",n1);
    sprintf(tmp2,"%04d",n2);
    for(i='0';i<='9';i++)map[i]=0;
    for(i=0;i<4;i++)
        map[tmp1[i]]++;
    for(i=0;i<4;i++)
        if(map[tmp2[i]]-->0)b--;
    for(i=0;i<4;i++)
        if(tmp1[i]==tmp2[i])a--,b++;
    for(i=0;i<4;i++)
        for(j=0;j<i;j++)
            if(tmp2[i]==tmp2[j])u[n2]=1;
    if(a || b)u[n2]=1;
}
main()
{
    int i,j,k,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&j,&k);
        for(i=0;i<10000;i++)
            go(n,i,j,k);
    }
    for(i=0,j=10000;i<10000;i++)
        j-=u[i];
    printf("%d\n",j);
}
