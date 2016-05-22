#include<cstdio>
char _var[]="%[.0123456789abcdefghijklmnopqrstuvwxyz]",
    _op[]="%[+-*/=\n]",_ph[]="()";
double calc(double x,double y,char o)
{
    if(o=='+')return x+y;
    if(o=='-')return x-y;
    if(o=='*')return x*y;
    if(o=='/')return x/y;
}
main()
{
    int i,j,assign;
    double num,var[30],s[1000];
    char a[10],b[10],t[1000];
    var[0]=10,var[1]=2;
    while(scanf("%c",a)==1)
    {
        assign=-1;
        if(a[0]>='a' && a[0]<='z')
        {
            scanf("%c",b);
            if(b[0]=='=')
                assign=a[0]-'a';
            else
            {
                ungetc(b[0],stdin);
                ungetc(a[0],stdin);
            }
        }else ungetc(a[0],stdin);
        i=j=0;
        while(1)
        {
            if(scanf(_var,a))
            {
                if(a[0]>='a' && a[0]<='z')
                    s[i++]=var[a[0]-'a'];
                else sscanf(a,"%lf",&s[i++]);
            }
            scanf("%c",b);
            if(b[0]==')')
            {
                while(t[j-1]!='(')
                    i--,s[i-1]=calc(s[i-1],s[i],t[--j]);
                j--;continue;
            }
            else if(b[0]=='\n')
            {
                while(j--)
                    i--,s[i-1]=calc(s[i-1],s[i],t[j]);
                break;
            }
            else if(b[0]=='+' || b[0]=='-')
                while(j && t[j-1]!='(')
                    i--,s[i-1]=calc(s[i-1],s[i],t[--j]);
            else
                while(j &&(t[j-1]=='*' || t[j-1]=='/'))
                    i--,s[i-1]=calc(s[i-1],s[i],t[--j]);
            t[j++]=b[0];
        }
        if(assign>=0)var[assign]=s[0];
        else printf("%.2lf\n",s[0]);
    }
}
