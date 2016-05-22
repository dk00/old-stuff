#include<cstdio>
bool check(char *s,int i)
{
    if(s[0]=='A' && i==1)
        return 1;
    if(i>2 && s[i-1]=='B' && s[i-2]=='A')
        return check(s,i-2);
    else if(i>2 && s[0]=='B' && s[i-1]=='A')
        return check(s+1,i-2);
    return 0;
}
main()
{
    int i,t;
    char s[10000];
    scanf("%d%c",&t,s);
    while(t--)
    {
        gets(s);
        for(i=0;s[i];i++);
        if(!s[1] && s[0]=='A')
            puts("SIMPLE");
        else if(i>2 && s[i-1]=='B' && s[i-2]=='A' && check(s,i))
            puts("FULLY-GROWN");
        else if(i>2 && s[0]=='B' && s[i-1]=='A' && check(s,i))
            puts("MUTAGENIC");
        else puts("MUTANT");
    }
}
