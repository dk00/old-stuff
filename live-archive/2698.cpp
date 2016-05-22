#include<cstdio>
#include<cstring>
int n;
char p[12][202],x[128];
int max(char s[])
{
    int i,j,k=0;;
    for(i=j=0;s[i];i++)
    {
        if((('a'<=s[i] && s[i]<='z')||('A'<=s[i] && s[i]<='Z'))&&!x[s[i]])
            j++;
        else
            j=0;
        if(j>5)return j;
        k>?=j;
    }
    return k;
}
char con1(char s[])
{
    return(max(s)>5);
}
char con2(char s[])
{
    if(max(s)<5)return 0;
    int i,j;
    for(i=j=0;i<n;i++)
        if(max(p[i])>4)j++;
    return j>2;
}
char con3(char s[])
{
    int i,j;
    for(i=j=0;i<n;i++)
        if(!strcmp(s,p[i]))j++;
    return j>1;
}
void add(char s[])
{
    int i;
    for(i=9;i>0;i--)
        strcpy(p[i],p[i-1]);
    strcpy(p[0],s);
    ++n;
    n<?=10;
}
main()
{
    x['a']=x['e']=x['i']=x['o']=x['u']=1;
    x['A']=x['E']=x['I']=x['O']=x['U']=1;
    int T;
    char tmp[1000];
    scanf("%d%c",&T,tmp);
    n=0;
    while(T--)
    {
        gets(tmp);
        if(con1(tmp)|| con2(tmp)|| con3(tmp))
            puts("n");
        else
            puts("y");
        add(tmp);
    }
}
