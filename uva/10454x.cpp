#include"bigintA03.h"
#include"Cnum.h"
bigint calc(char *s)
{
    int i,j,n=0,cnt=0,star=1;
    bigint sum,num[100];
    if(s[0]=='(')
    {
        for(i=1,cnt=1;cnt && s[i];i++)
        {
            if(s[i]=='(')cnt++;
            if(s[i]==')')cnt--;
        }
        if(!s[i])
        {
            s[i-1]=0;
            return calc(s+1);
        }
    }
    for(cnt=0,i=0;s[i];i++)
    {
        if(s[i]=='(')cnt++;
        if(s[i]==')')cnt--;
        if(cnt)continue;
        if(s[i]=='+')star=0;
    }
    for(i=0;s[i];i++)
    {
        if(s[i]=='*' || s[i]=='+')continue;
        if(s[i]=='(')
        {
            cnt=1;
            for(j=i+1;cnt;j++)
            {
                if(s[j]=='(')cnt++;
                if(s[j]==')')cnt--;
            }
        }
        else j=i+1;
        if(star || s[j]!='*')
        {
            if(j==i+1)
                num[n++]=1;
            else
            {
                s[j-1]=0;
                num[n++]=calc(s+i+1);
                s[j-1]=')';
            }
        }
        else
        {
            for(cnt=0,j++;cnt || (s[j] && s[j]!='+');j++)
            {
                if(s[j]=='(')cnt++;
                if(s[j]==')')cnt--;
                if(cnt)continue;
            }
            char tmp;tmp=s[j],s[j]=0;
            num[n++]=calc(s+i);
            s[j]=tmp;
        }
        i=j-1;
    }
    for(i=0,sum=1;i<n;i++)
        sum*=num[i];
    return sum*C[n];
}
main()
{
    setcnum();
    char s[1000];
    while(scanf("%s",s)!=EOF)
        printf("%s\n",calc(s).tostring());
}
