/*
PROG: latin
LANG: C++
ID: s0000151
*/
#include<cstdio>
char v[128];
main()
{
    freopen("latin.in","r",stdin);
    freopen("latin.out","w",stdout);
    int T;
    char s[100];
    v['a']=v['e']=v['i']=v['o']=v['u']=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);
        if(v[s[0]])
            printf("%scow\n",s);
        else
            printf("%s%cow\n",s+1,s[0]);
    }
    scanf(" ");
}
