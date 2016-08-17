#include<cstdio>
int t[256];
main()
{

    t['B']=t['F']=t['P']=t['V']=1;
    t['C']=t['G']=t['J']=t['K']=t['Q']=t['S']=t['X']=t['Z']=2;
    t['D']=t['T']=3;
    t['L']=4;
    t['M']=t['N']=5;
    t['R']=6;
    char s[1000];
    while(gets(s))
    {
        if(t[s[0]])
            printf("%d",t[s[0]]);
        for(int i=1;s[i];i++)
            if(t[s[i]] && t[s[i]]!=t[s[i-1]])
                printf("%d",t[s[i]]);
        puts("");
    }
}
