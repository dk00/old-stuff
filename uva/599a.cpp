#include<cstdio>
#include<iostream>
char buf[8000005];
main()
{
    char a,b,s[256];
    int i,j,T;
    fread(buf,1,8000000,stdin);
    for(i=0;buf[i]!='\n';i++);
    i++;
    while(buf[i])
    {
        for(char x='A';x<='Z';x++)s[x]=0;
        a=b=0;
        while(buf[i]!='*')
        {
            b--;
            if(!s[buf[++i]]++)a--;
            if(!s[buf[i+2]]++)a--;
            i+=5;
        }
        while(buf[i]!='\n')i++;
        i++;
        for(j=i;buf[i]!='\n';i++);
        i++;
        a+=(j=i-j)>>=1,b+=j;
        std::
        cout << "There are " << 0+b-a <<" tree(s) and " << 0+a <<" acorn(s).\n";
    }
}
