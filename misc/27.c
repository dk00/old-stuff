main()
{
    char a[9],b[9];
    int i,j;
    scanf("%s %s",a,b);
    for(i=j=0;b[i];i++)
        j+=!strncmp(a,b+i,2);
    printf("%d\n",j);
}
