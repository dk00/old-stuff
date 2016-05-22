#include<cstdio>
int n,u[128];
char path[9999],tmp[9999];
void go(int d)
{
    if(d>=n)
    {
        puts(path);
        return;
    }
    for(int i='A';i<='Z';i++)
    {
        if(u[i])
        {
            u[i]--;
            path[d]=i;
            go(d+1);
            u[i]++;
        }
        if(u[i-'A'+'a'])
        {
            u[i-'A'+'a']--;
            path[d]=i-'A'+'a';
            go(d+1);
            u[i-'A'+'a']++;
        }
    }
}
main()
{
    int i,T;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<128;i++)
            u[i]=0;
        scanf("%s",tmp);
        for(n=0;tmp[n];n++)
            u[tmp[n]]++;
        path[n]=0;
        go(0);
    }
}
