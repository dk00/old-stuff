#include<cstdio>
char a[100000],s[1000][257];
int n,path[10000];
void go(int d,char *r)
{
    if(!r[d])
    {
        a[d]=0;
        for(int i=0;i<d;i++)
        {
            if(r[i]=='#')
                printf("%s",s[path[i]]);
            else
                putchar(path[i]+'0');
        }
        puts("");
        return;
    }
    if(r[d]=='#')
        for(int i=0;i<n;i++)
        {
            path[d]=i;
            go(d+1,r);
        }
    else
        for(int i=0;i<10;i++)
        {
            path[d]=i;
            go(d+1,r);
        }
}
main()
{
    int i,m;
    char r[1000];
    while(scanf("%d%c",&n,r)==2)
    {
        puts("--");
        for(i=0;i<n;i++)
            gets(s[i]);
        scanf("%d%c",&m,r);
        while(m--)
            go(0,gets(r));
    }
}
