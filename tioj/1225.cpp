#include<cstdio>
int s[1000001];
long long go(int st,int ed)
{
    if(st>=ed)return 0;
    int i,j;
    for(i=j=st;i<=ed;i++)
        if(s[i]>s[j])j=i;
    if(s[ed]==s[j])j=ed;
    return go(st,j-1)+go(j+1,ed)+s[j]*((j!=st)+(j!=ed));
}
main()
{
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    printf("%I64d\n",go(0,n-1));
}
//25 **
//****

