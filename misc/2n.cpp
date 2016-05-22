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
        if(t[0]=='0')
        {
            assign(t+1,len-1);
            return;
        }
        int i;
        d=len;
        for(i=0;i<d;i++)
            s[i]=t[i];
        rev();
        s[d]='\0';
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
        s[0]++;
        for(i=0;s[i]>'9';i++)
            s[i]='0',s[i+1]++;
        if(s[d]!='\0')
            s[d]='1',s[d+++1]='\0';
    }
    bool operator--()
    {
        int i;
        s[0]--;
        for(i=0;s[i]<'0';i++)
            s[i]+=10,s[i+1]--;
        if(s[d-1]=='0')
            s[--d]='\0';
    }
};
int check(char *a,char *b,int i,int j)
{
    int k;
    for(k=i-j;a[k]=='9' && (b[k]=='0'||b[k]==0) && k<i;k++);
    if(k>=i)
    {
        for(k=i-j;k<i;k++)
            a[k]='0';
        return 1;
    }
}
main()
{
    int i,j,k,pren,n,find;
    char s[601],temp[601],pre[601];
    num test,tricky;
    bigint ans,tmp1,tmp2,tmp3;
    for(i=0;i<201;i++)
        s[i]='?';
    for(;i<600;i++)
        s[i]=0;
    while(scanf("%s",s+200)==1)
    {
        for(n=200;s[n];n++);
        find=0,tmp1=0,tmp2=0,tmp3=9;
        for(i=1;;i++)
        {
            for(j=0;j<i;j++)
            {
                strncpy(temp,s+200+j,i-j);
                strncpy(temp+i-j,s+200,j);
                temp[i]=0;
                if(temp[0]=='0')
                    continue;
                if(check(temp,s+200+j,i,j))
                    test.assign(temp,i),--test;
                else test.assign(temp,i);
                if(j>0)
                    ++test;
                for(k=j;test==(s+200+k) && k+200<n;k+=test.d,++test);
                if(k+200>=n)
                {
                    if(!find || strcmp(temp,pre)<0)
                        pren=j,strcpy(pre,temp);
                    find=1;
                }
            }
            if(find)
                break;
            tmp2+=tmp3;
            tmp1+=tmp2;
            tmp2*=10;
            tmp3*=10;
        }
        j=pren;
        pre[0]--;
        test.assign(pre,i);
        test.rev();
        ans=test.s,ans*=i;
        if(j>0) tmp2=i-j+1;
        else tmp2=1;
        ans+=tmp2,ans+=tmp1;
        puts(ans.tostring());
    }
}
