#include<cstdio>
#include<cstring>
#include<algorithm>
int n;
char s[1000000];
struct a
{
    int k;
    bool operator<(a b)const
    {
        return(strncmp(s+k,s+b.k,n)<0);
    }
    bool operator==(a b)const
    {
        return(strncmp(s+k,s+b.k,n)==0);
    }
    void print()
    {
        for(int i=0;i<n;i++)
            putchar(s[i+k]);
        puts("");
    }
}u[1000000];
main()
{
    int i,j,k,max,ans;
    while(scanf("%d %s",&n,s)==2)
    {
        for(i=0;s[i];i++);
        i-=n;
        for(j=0;j<=i;j++)
            u[j].k=j;
        std::sort(u,u+i+1);
        for(j=max=0;j<=i;j++)
        {
            for(k=0;k+j<=i && u[j]==u[j+k];k++);
            if(k>max)max=k,ans=j;
        }
        u[ans].print();
    }
}
