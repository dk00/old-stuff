#include<cstdio>
char buf[11534336];
char ch[256];
main()
{
    freopen("599.in","r",stdin);
    int i;
    char s[256],x[2];
    for(i='A';i<='Z';i++)ch[i]=1;
    ch['*']=2,ch['(']=ch[')']=3,ch['\n']=4;
    fread(buf,1,11534336,stdin);
    for(i=0;buf[i]!='\n';i++);
    i++;
    while(buf[i])
    {
        for(char j='A';j<='Z';j++)s[j]=0;
        while(ch[buf[i]]<2)i++;
        if(ch[buf[i]]==3)
            while(ch[buf[i]]!=2)
            {
                if(ch[buf[i]]==1)s[buf[i]]=1;
                i++;
            }
        while(ch[buf[i]]<4)i++;
        i++;x[0]=x[1]=0;
        while(ch[buf[i]]<4)
        {
            if(ch[buf[i]]==1)x[s[buf[i]]]++;
            i++;
        }
        printf("There are %d tree(s) and %d acorn(s).\n",*x,x[1]);
    }
}
