#include<cstdio>
bool notp[10000];
main()
{
    int i,j;
    char s[100],c[128];
    for(i='a';i<='z';i++)c[i]=i-'a'+1;
    for(i='A';i<='Z';i++)c[i]=i-'A'+27;
    for(i=3;i<1090;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*3;j<1090;j+=i*2)notp[j]=1;
    }
    while(scanf("%s",s)==1)
    {
        for(i=j=0;s[i];i++)j+=c[s[i]];
        if((notp[j] || j%2==0) && j!=2)
            puts("It is not a prime word.");
        else
            puts("It is a prime word.");
    }
}
