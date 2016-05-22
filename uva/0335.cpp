#include<cstdio>
#include<algorithm>
using namespace std;
int n,num,low,grey,s[99];
void go(int d)
{
    if(d+num>=low)return;
    if(grey>=0)
    {
        low<?=num+d;
        return;
    }
    int i,j,k,tmp;
    for(i=j=0;i<n;i++)
        if(s[i])j++;
    if(j<3)
    {
        for(i=0;i<n;i++)
            s[i]+=50;
        go(d+1);
        for(i=0;i<n;i++)
            s[i]-=50;
        return;
    }
    for(i=0;!s[i];i++);
    for(j=i+1;j<n;j++)
        if(s[j])for(k=j+1;k<n;k++)
            if(s[k])
            {
                tmp=s[i]<?s[j]<?s[k]<?49;
                s[i]-=tmp,s[j]-=tmp,s[k]-=tmp;
                grey+=tmp;
                go(d);
                grey-=tmp;
                s[i]+=tmp,s[j]+=tmp,s[k]+=tmp;
            }
}
main()
{
    int i;
    while(scanf("%d",&n) && n)
    {
        for(i=num=0;i<n;i++)
        {
            scanf("%d",&s[i]);
            s[i]=-s[i];
        }
        scanf("%d",&grey);
        while(1)
        {
            for(i=0;i<n;i++)
                if(s[i]<0)break;
            if(i>=n)break;
            for(i=0;i<n;i++)
                s[i]+=50;
            num++;
        }
        while(grey--)
        {
            sort(s,s+n);
            if(s[n-3]<=0)
                for(num++,i=0;i<n;i++)
                    s[i]+=50;
            s[n-1]--,s[n-2]--,s[n-3]--;
        }
        printf("%d\n",num);
    }
}
