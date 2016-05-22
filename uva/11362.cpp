#include<cstdio>
#include<algorithm>
bool cmp(const char *a,const char *b)
{
    int i;
    for(i=0;a[i] && b[i];i++)
        if(a[i]!=b[i])
            return a[i]<b[i];
    return 0;
}
char *s[10001];
main()
{
    int i,j,k,n,T;
    scanf("%d",&T);
    for(i=0;i<10000;i++)
        s[i]=new char[11];
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
        std::sort(s,s+n,cmp);
        for(i=1;i<n;i++)
        {
            for(j=k=0;!k && s[i-1][j] && s[i][j];j++)
                if(s[i][j]!=s[i-1][j])k=1;
            if(!k)break;
        }
        if(i<n)puts("NO");
        else puts("YES");
    }
}
