#include<cstdio>
char s[50],c[128];
main()
{
    int i;
    c['A']=c['B']=c['C']='2';
    c['D']=c['E']=c['F']='3';
    c['G']=c['H']=c['I']='4';
    c['J']=c['K']=c['L']='5';
    c['M']=c['N']=c['O']='6';
    c['P']=c['Q']=c['R']=c['S']='7';
    c['T']=c['U']=c['V']='8';
    c['W']=c['X']=c['Y']=c['Z']='9';
    while(gets(s))
    {
        for(i=0;s[i];i++)
            if('A'<=s[i] && s[i]<='Z')s[i]=c[s[i]];
        puts(s);
    }
}
