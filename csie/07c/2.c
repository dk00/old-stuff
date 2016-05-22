main()
{
    int i,j,year,month,day,hint;
    scanf("%d %d %d",&year,&month,&hint);
    if(year<1000 || 3000<year || month<=0 || month>12 || hint<0 || hint>=7)
    {
        puts("invalid");
        return;
    }
    puts(" Su Mo Tu We Th Fr Sa");
    puts("=====================");
    for(j=0;j<hint;j++)
        printf("   ");
    if(month==2)
        if(year%100==0)
            day=28+!(year%400);
        else
            day=28+!(year%4);
    else if(month<8)
        day=30+month%2;
    else
        day=30+!(month%2);
    for(i=1,j=hint;j<7;i++,j++)
        printf("%3d",i);
    puts("");
    while(i<=day)
    {
        for(j=0;j<7 && i<=day;i++,j++)
            printf("%3d",i);
        puts("");
    }
    puts("=====================");
}
