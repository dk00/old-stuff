#include<cstdio>
int v;
int go(int c)
{
    if(c==1)return v++;
    int i,j=v+(1<<(c-1))-1;
    for(i=1;i<c;i++)
        printf("%d %d\n",go(i),j);
    return v++;
}
main()
{
    int i,n;
    while(scanf("%d",&n)==1)
    {
        printf("%d %d\n",1<<(n-1),(1<<(n-1))-1);
        v=1,go(n);
        for(i=1;i<v-1;i++)
            printf("%d ",i);
        printf("%d\n",v-1);
    }
}
