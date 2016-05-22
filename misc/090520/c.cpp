#include<cstdio>
int s[1000001];
main()
{
    int i,j,n,x,T;
    freopen("pc.in","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(i=0;i<n;i++)
            s[i+1]=n+1;
        for(j=0;j<3;j++){
            scanf("%d",&x);
            for(i=0;i+x<=n;i++)
                s[i+x]<?=s[i]+1;
        }
        for(i=n;s[i]>n;i--);
        printf("%d %d\n",n-i,s[i]);
    }
}
