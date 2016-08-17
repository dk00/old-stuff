#include<cstdio>
double getnum()
{
    int i;
    char c,s[1000];
    double num,r=1;
    scanf("%c",&c);
    while(c=='+' || c=='-')
    {
        if(c=='-')r=-r;
        scanf("%c",&c);
    }
    for(i=0;c>='0' && c<='9' || c=='.';i++)
        s[i]=c,scanf("%c",&c);
    s[i]=0,ungetc(c,stdin);
    sscanf(s,"%lf",&num);
    return num*r;
}
main()
{
    int i,j;
    double var,now,tmp;
    char c,d,o,s[1000];
    while(scanf("%c",&c)==1)
    {
        ungetc(c,stdin);
        var=0,o='+',tmp=getnum();
        scanf("%c",&c);
        while(c!='\n')
        {
            now=getnum();
            if(c=='*')tmp*=now;
            if(c=='/')tmp/=now;
            if(c=='+' || c=='-')
            {
                if(o=='+')var+=tmp;
                if(o=='-')var-=tmp;
                tmp=now,o=c;
            }
            scanf("%c",&c);
        }
        if(o=='+')var+=tmp;
        if(o=='-')var-=tmp;
        printf("%.3lf\n",var);
    }
}
