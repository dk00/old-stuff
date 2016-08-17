#include<cstdio>
int s[205][10001];
void go(int i,int j)
{
    if(i<=0)return;
    go(i-1,s[i][j]);
    if(s[i][j]==j)puts("port");
    else puts("starboard");
}
main()
{
    int i,j,k,n,sum,min,max,T;
    s[0][0]=1;
    for(j=1;j<=10000;j++)s[0][j]=-1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        n*=100;
        for(i=0,min=max=sum=0;scanf("%d",&k) && k;)
        {
            sum+=k;
            if(min<0)continue;
            else i++;
            for(j=n,min=-1;j>=0;j--)
                if(sum-j<=n && s[i-1][j]>=0)
                    s[i][j]=j,min=j;
                else if(j-k>=0 && s[i-1][j-k]>=0)
                    s[i][j]=j-k,min=j;
                else s[i][j]=-1;
            if(min>=0)max=i;
        }
        printf("%d\n",max);
        for(j=n;s[max][j]<0;j--);
        go(max,j);
        if(T)puts("");
    }
}
