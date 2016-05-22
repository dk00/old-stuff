#include<cstdio>
const int N=5340245;
int s[N];
main()
{
    int i,j,k,n,T;
    for(i=1;i<N;i++)
        for(j=2,s[i]>?=1;j<=i && i*j<N;j++)
                s[i*j]=s[i]+s[j];
    
    for(i=3;i<N;i++)
        s[i]+=s[i-1];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0,j=N-1;i<j;)
        {
            k=(i+j)/2;
            if(s[k]<=n)i=k+1;
            else j=k;
        }
        printf("%d\n",i);
    }
}
