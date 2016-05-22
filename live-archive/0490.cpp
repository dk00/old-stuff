#include<cstdio>
const int M=10001,z=9792;
int pow(int n,int k)
{
    if(!k)return 1;
    if(k%2)return 1ll*n*pow(n,k-1)%M;
    n=pow(n,k/2);
    return n*n%M;
}
int n,s[M];
int sol(int a,int x)
{
    for(int i=0;i<M;i++)
        if(a*i%M==x)return i;
    return -1;
}
char test(int a)
{
    int x=(s[2]-1ll*a*a*s[0]+M)%M;
    int b=sol((a+1),x);
    if(b<0)return 0;
    for(int i=1;i<2*n;i++,i++)
    {
        s[i]=(s[i-1]*a+b)%M;
        if(i+1<n*2 && s[i+1]!=(s[i]*a+b)%M)return 0;
    }
    return 1;
}
main()
{
    int i;
    scanf("%d",&n);
    if(!n)return 0;
    for(i=0;i<2*n;i++,i++)
        scanf("%d",s+i);
    if(n==1)
    {
        printf("%d\n",s[0]);
        return 0;
    }
    for(i=0;i<10001;i++)
        if(test(i))break;
    for(i=1;i<2*n;i++,i++)
        printf("%d\n",s[i]);
}
