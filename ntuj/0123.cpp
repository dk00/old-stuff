#include<cstdio>
int getnum()
{
    int a,b;
    scanf("%d.%d",&a,&b);
    return a*100+b;
}
int n,s[10001];
char go(int m,int len)
{
    if(!len)return 1;
    long long i,j;
    for(i=j=0;j<m && i<n;i++)
        j+=s[i]/len;
    return j>=m;
}
main()
{
    int i,j,k,m,max;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=j=0;i<n;i++)
            j>?=(s[i]=getnum());
        for(i=max=0;i<=j;)
        {
            k=(i+j)/2;
            if(go(m,k))max=k,i=k+1;
            else j=k-1;
        }
        printf("%d.%02d\n",max/100,max%100);
    }
}
