#include<cstdio>
#include<cstring>
int n;
long long s[100002],t[100002],p[100002];
char go(long long v)
{
    int i;
    memcpy(t,s,n*sizeof(s[0]));
    for(i=0;i+1<n;i++)
        if(t[i]<v)
            t[i+1]-=p[i+1]-p[i]+v-t[i];
        else if(t[i]-v>p[i+1]-p[i])
            t[i+1]+=t[i]-v-p[i+1]+p[i];
    return(t[i]>=v);
}
main()
{
    long long int i,j,k,max;
    while(scanf("%d",&n)==1)
    {
        for(i=j=0;i<n;i++)
            scanf("%lld %lld",p+i,s+i),j+=s[i];
        j/=n;
        for(i=max=0;i<=j;)
        {
            k=(i+j)/2;
            if(go(k))max>?=k,i=k+1;
            else j=k-1;
        }
        printf("%lld\n",max);
    }
}
