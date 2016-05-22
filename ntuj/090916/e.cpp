#include<cstdio>
using namespace std;
const int N=3000001,M=1000000;
int p[N];
main()
{
    int i,j,T;
    freopen("pb.in","r",stdin);
    for(i=1;i<N;i++)
        p[i]=i;
    for(i=1;i<N;i++)
        for(j=i*2;j<N;j+=i)
            p[j]-=p[i];
    for(i=2;i<N;i++)
        (p[i]+=p[i-1])%=M;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&i);
        if(i>=1814)
            printf("%06d\n",p[i]);
        else
            printf("%d\n",p[i]);
    }
}
