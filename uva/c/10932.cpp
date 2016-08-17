#include<cstdio>
double s[26];
double eval(char *&exp);
double getval(char *&exp);
double getval(char *&exp)
{
    double num;
    if(exp[0]=='(')
    {
        num=eval(++exp);
        exp++;
        return num;
    }
    if(exp[0]>='a' && exp[0]<='z')
        num=s[*(exp++)-'a'];
    else
        for(num=0.0;exp[0]>='0' && exp[0]<='9';exp++)
            num=num*10+exp[0]-'0';
    return num;
}
double eval(char *&exp)
{
    double num=getval(exp);
    if(exp[0]==0)
        return num;
    if(exp[0]=='*' || exp[0]=='/')
        while(exp[0] && exp[0]!=')' && exp[0]!='+' && exp[0]!='-')
        {
            if(exp[0]=='*')
                num*=getval(++exp);
            else num/=getval(++exp);
        }
    else
        while(exp[0] && exp[0]!=')')
        {
            if(exp[0]=='+')
                num+=eval(++exp);
            else num-=eval(++exp);
        }
    return num;
}
main()
{
    int i;
    char exp[10000],*p;
    for(i=0;i<26;i++)s[i]=0;
    while(gets(exp))
    {
        if(exp[1]=='=')
            s[exp[0]-'a']=eval((p=exp+2));
        else
            printf("%.2lf\n",eval(p=exp));
    }
}
