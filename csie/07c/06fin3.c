main()
{
    int i,j;
    int c[266];
    for(i=0;i<256;i++)c[i]=i;
    for(i='a',j='Z';i<='z';i++,j--)
        c[i]=j,c[j]=i;
    for(i='0';i<'9';i++)
        c[i]=i+1;
    c['9']='0';
    while((i=getchar())!=-1)
        putchar(c[i]);
}
