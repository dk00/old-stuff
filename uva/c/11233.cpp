#include<cstdio>
#include<cstring>
char s1[20][21],s2[20][21];
main()
{
    int i,n,m;
    char s[99];
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%s %s",s1[i],s2[i]);
    while(m--)
    {
        scanf("%s",s);
        for(i=0;i<n;i++)
            if(!strcmp(s,s1[i]))
            {
                puts(s2[i]);
                goto next;
            }
        i=strlen(s);
        if(i>1 && s[i-2]!='a' && s[i-2]!='e' && s[i-2]!='i' && s[i-2]!='o'
        && s[i-2]!='u' && s[i-1]=='y')
            strcpy(s+i-1,"ies");
        else if(s[i-1]=='o' || s[i-1]=='s' || s[i-1]=='x' ||
        (i>1 && s[i-1]=='h' &&(s[i-2]=='c' || s[i-2]=='s')))
            strcpy(s+i,"es");
        else
            strcpy(s+i,"s");
        puts(s);
        next:;
    }
}
