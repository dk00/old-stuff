/*
LANG:C++
TASK:namenum
*/
#include<cstdio>
#include<string>
#include<algorithm>
bool cmp1(const char w[],char num[])
{
    int i;
    char tmp[13];
    for(i=0;w[i];i++)
        tmp[i]=(w[i]-'A'-(w[i]>'Q'))/3+'2';
    tmp[i]=0;
    for(i=0;tmp[i] || num[i];i++)
        if(tmp[i]!=num[i])return 0;
    return 1;
}
std::string s[5000];
char tmp[13];
main()
{
    int i,n,x=0;
    FILE *fp=fopen("dict.txt","r");
    for(n=0;fscanf(fp,"%s",tmp)==1;n++)s[n]=tmp;
    std::sort(s,s+n);
    freopen("namenum.in","r",stdin);
    freopen("namenum.out","w",stdout);
    scanf("%s",tmp);
    for(i=0;i<n;i++)
        if(cmp1(s[i].c_str(),tmp))
            puts(s[i].c_str()),x++;
    if(!x)puts("NONE");
}
