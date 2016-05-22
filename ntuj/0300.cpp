#include<set>
#include<cstdio>
#include<string>
using namespace std;
struct pa
{
    string tmp;
    int x;
    bool operator<(pa a)const{return tmp<a.tmp;}
};
set<pa> h;
struct pro
{
    char name[99];
    int n,s[101],a[101],b[101];
    void get()
    {
        int i;
        char t0[99],t1[99];
        scanf("%s",name);
        scanf("%d%c",&n,t0);
        for(i=0;i<n;i++)
        {
            gets(t0);
            if(sscanf(t0,"%s %d",t1,a+i)==2)
                b[i]=a[i];
            else b[i]=a[i]=-1;
            if(h.count((pa){t1,0})==0)
                h.insert((pa){t1,h.size()});
            s[i]=h.find((pa){t1,0})->x;
        }
    }
    void proc()
    {
        int i,j,k,l,x,st,sum=100,tmp[101],t0[101];
        char c[101];
        for(st=0;a[st]>=0 && st<n;st++);
        if(st>=n)return;
        c[st]=1;
        a[n]=1;
        for(i=n-1;i>=st;i--)
        {
            if(a[i]<0)a[i]=a[i+1],c[i]=1;
            else c[i]=0;
            sum-=a[i];
        }
        for(i=st;i<n;i++)
        {
            if(!c[i])continue;
            for(j=0;j<n;j++)
                tmp[j]=a[j];
            for(k=i;k>=0 && c[k];k--);
            for(l=sum,j=k+1;l>0 && (k<0 || tmp[i]<b[k]);l--)
            {
                tmp[j++]++;
                if(j>i)j=k+1;
            }
            b[i]=tmp[i];
        }
        for(j=0;j<n;j++)
            t0[j]=a[j];
        for(i=st;i<n;i++)
        {
            if(!c[i])continue;
            for(l=i;l<n && c[l];l++);
            for(j=0;j<n;j++)
                tmp[j]=t0[j];
            int u=1;
            for(k=sum;k>0 && u;)
                for(j=u=0;k>0 && j<n;j++)
                {
                    if(j>=i && j<l)continue;
                    if(!j || (tmp[j]<tmp[j-1]))
                        tmp[j]++,k--,u=1;
                }
            for(x=i;x>=0 && c[x];x--);
            for(j=x+1;k>0;k--)
            {
                tmp[j++]++;
                if(j>=l)j=i;
            }
            a[i]=tmp[i];
        }
    }
    int findb(int aa)
    {
        for(int i=0;i<n;i++)
            if(s[i]==aa)
                return b[i];
        return 0;
    }
    int finda(int aa)
    {
        for(int i=0;i<n;i++)
            if(s[i]==aa)
                return a[i];
        return 0;
    }
}s[99];
main()
{
    int i,j,k,n,m;
    char tmp[99];
    while(scanf("%d",&n) && n)
    {
        h.clear();
        for(i=0;i<n;i++)
            s[i].get(),s[i].proc();
        scanf("%d",&m);
        while(m--)
        {
            scanf("%s",tmp);
            if(((string)tmp)=="most")
            {
                scanf("%s",tmp);
                if(h.count((pa){tmp,0}))
                    k=h.find((pa){tmp,0})->x;
                else k=-1;
                for(i=j=0;i<n;i++)
                    j>?=s[i].finda(k);
                for(i=0;i<n;i++)
                    if(s[i].findb(k)>=j)break;
                printf("%s",s[i].name);
                for(i++;i<n;i++)
                    if(s[i].findb(k)>=j)
                        printf(" %s",s[i].name);
                puts("");
            }
            else
            {
                scanf("%s",tmp);
                if(h.count((pa){tmp,0}))
                    k=h.find((pa){tmp,0})->x;
                else k=-1;
                for(i=j=0;i<n;i++)
                    j<?=s[i].findb(k);
                for(i=0;i<n;i++)
                    if(s[i].finda(k)<=j)break;
                printf("%s",s[i].name);
                for(i++;i<n;i++)
                    if(s[i].finda(k)>=j)
                        printf(" %s",s[i].name);
                puts("");
            }
        }
    }
}
