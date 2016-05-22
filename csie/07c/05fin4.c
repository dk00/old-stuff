int c[256];
main()
{
    int i,j;
    char tmp[999];
    for(i='a';i<='z';i++)c[i]=2;
    for(i='A';i<='Z';i++)c[i]=3;
    c['A']=c['E']=c['I']=c['O']=c['U']=6;
    c['a']=c['e']=c['i']=c['o']=c['u']=5;
    while(scanf("%s",tmp) && strcmp(tmp,"end"))
    {
        for(i=j=0;tmp[i];i++)
            j+=c[tmp[i]];
        printf("%d\n",j);
    }
}
