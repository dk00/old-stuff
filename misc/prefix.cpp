#include<cstdio>
/*char *prefixD(char*& s,char*& res)
{
    if(*s==')' || !*s)
    if(*s=='(')
        return prefixD(++s);
    if(*s<'0' || *s>'9')
    {
        *res++=*s;
        *res++=' ';
        
    }
    return res;
}*/
int stack1[10000];

char *prefix(char s[],char res[])
{
    int i;
    for(i=0;s[i]!=0;i++)
    {

    }
}

int eval1(char*& s)
{
    while(*s==' ')s++;
    if(*s>='0' && *s<='9')
    {
        int n=0;
        while(s[0]>='0' && s[0]<='9')
            n=n*10+*s++-'0';
        return n;
    }
    if(*s=='+')
        return eval1(++s)+eval1(s);
    if(*s=='-')
        return eval1(++s)-eval1(s);
    if(*s=='*')
        return eval1(++s)*eval1(s);
    if(*s=='/')
        return eval1(++s)/eval1(s);
    if(*s=='%')
        return eval1(++s)%eval1(s);
}
char stack[10000];

int eval(char *s)
{
    int i,num1,num2,top=0;
    char op=0;
    for(i=0;s[i]!=0;i++)
    {
        if(s[i]==' ')
            continue;
        if(s[i]<'0' || s[i]>'9')
        {
            stack[top++]=s[i];
            continue;
        }
        num2=0;
        while(s[i]>='0' && s[i]<='9')
            num2=num2*10+s[i++]-'0';
        op=stack[--top];
        if(op=='+')
            num1+=num2;
        if(op=='-')
            num1-=num2;
        if(op=='*')
            num1*=num2;
        if(op=='/')
            num1/=num2;
        op=0;
    }
    return num1;
}
main()
{
    char tmp[100],*s;
    while(gets(s=tmp))
        printf("%d\n",eval(s));
}
