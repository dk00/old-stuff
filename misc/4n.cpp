#include"bigintA03.h"
struct num
{
    int d;
    char s[201];
    void rev()
    {
        int i,j;
        for(i=0;i<d/2;i++)
            j=s[i],s[i]=s[d-i-1],s[d-i-1]=j;
    }
    void assign(char *t,int len)
    {
        int i;
        s[d=len]=0;
        for(i=0;i<d;i++)
            s[i]=t[i];
        rev();
    }
    bool operator==(char *t)
    {
        int i;
        for(i=0;i<d && t[i]!='\0';i++)
            if(s[d-i-1]!=t[i] && t[i]!='?')
                break;
        return (i>=d || t[i]=='\0');
    }
    bool operator++()
    {
        int i;
        for(i=0,s[0]++;s[i]>'9';i++)
            s[i]='0',s[i+1]++;
        if(s[d]!='\0')
            s[d]='1',s[d+++1]='\0';
    }
    bool operator--()
    {
        int i;
        for(i=0,s[0]--;s[i]<'0';i++)
            s[i]+=10,s[i+1]--;
        if(s[d-1]=='0')
            s[--d]='\0';
    }
};
main()
{
    num test;
    int i,j,k,n,fix,pren,find;
    bigint num1,num2,num3,ans;
    char p[500],*s=p+200,nine[201],zero[201],now[201],pre[201];
    for(i=0;i<200;i++)
        p[i]='?',zero[i]='0',nine[i]='9';
    while(scanf("%s",s)==1)
    {
        find=0,n=strlen(s);
        num1=0,num2=0,num3=9;
        for(i=1;i<=n;i++)
        {
            for(j=0;j<i;j++)
            {
                strncpy(now,nine,i),now[i]=0;
                test.assign(now,i);
                for(k=0-j;test==(s+k) && k<n;k+=test.d,++test);
                if(k>=n)
                {
                    if(!find || strcmp(pre,now)>0)
                        pren=j,strcpy(pre,now);
                    find=1;
                }
                strncpy(now,s+i-j,j);
                strncpy(now+j,s,i-j);
                if(now[0]=='0')continue;
                test.assign(now,i);
                for(k=0-j;test==(s+k) && k<n;k+=test.d,++test);
                if(k>=n)
                {
                    if(!find || strcmp(pre,now)>0)
                        pren=j,strcpy(pre,now);
                    find=1;
                }
                strncpy(now+j,zero,i-j);
                test.assign(now,i),--test;
                test.rev(),strcpy(now,test.s),test.rev();
                for(k=0-j;test==(s+k) && k<n;k+=test.d,++test);
                if(k>=n)
                {
                    if(!find || strcmp(pre,now)>0)
                        pren=j,strcpy(pre,now);
                    find=1;
                }
            }
            if(find)break;
            num2+=num3,num1+=num2;
            num2*=10,num3*=10;
        }
        if(i>n)
        {
            pren=0;
            if(s[0]!='0')
                strcpy(pre,s);
            else
                pren++,pre[0]='1',strcpy(pre+1,s);
        }
        pre[0]--,test.assign(pre,i);
        test.rev(),ans=test.s,ans*=i;
        if(pren>0)num2=pren+1;
        else num2=1;
        ans+=num1,ans+=num2;
        puts(ans.tostring());
    }
}
