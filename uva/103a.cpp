#include<cstdio>
#include<algorithm>
int n,m;
struct box
{
    int u,len[11];
    bool operator<(box a)const
    {
        int i;
        for(i=0;len[i]==a.len[i] && i<m-1;i++);
        return(len[i]<a.len[i]);
    }
    bool operator<=(box a)
    {
        int i;
        for(i=0;len[i]<a.len[i] && i<m;i++);
        return(i>=m);
    }
}s[35];
main()
{
    int i,j,max,p[35],l[35],tmp[35];
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
        {
            s[i].u=i+1;
            for(j=0;j<m;j++)
                scanf("%d",&s[i].len[j]);
            std::sort(s[i].len,s[i].len+m);
            p[i]=-1,l[i]=1;
        }
        std::sort(s,s+n);
        for(i=max=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
                if(s[i]<=s[j] && l[i]+1>l[j])
                    l[j]=l[p[j]=i]+1;
            if(l[i]>l[max])max=i;
        }
        printf("%d\n",l[max]);
        for(i=max,j=0;p[i]>=0;i=p[i])
            tmp[j++]=i;
        printf("%d",s[i].u);
        while(j--)
            printf(" %d",s[tmp[j]].u);
        puts("");
    }
}
