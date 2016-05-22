#include<cstdio>
#include<algorithm>
using namespace std;
int s[1501],t1[1125750],t2[1125750];
int gen(int s[],int n,int t[])
{
    int i,j,k,m=0;
    for(i=0;i<n;i++)
        for(j=i,k=s[i];j<n;k+=s[++j])
            t[m++]=k;
    std::sort(t,t+m);
    return m;
}
main()
{
    int i,j,n1,n2,w,h;
    long long sum;
    while(scanf("%d %d",&n1,&n2)==2 && n1+n2)
    {
        for(i=0;i<n1;i++)
            scanf("%d",s+i);
        n1=gen(s,n1,t1);
        for(i=0;i<n2;i++)
            scanf("%d",s+i);
        n2=gen(s,n2,t2);
        for(i=j=sum=0;i<n1;i++)
        {
            for(h=1;i+1<n1 && t1[i]==t1[i+1];i++,h++);
            while(j<n2 && t2[j]<t1[i])j++;
            if(t1[i]!=t2[j])continue;
            for(w=1;j+1<n2 && t2[j]==t2[j+1];j++,w++);
            sum+=1ll*h*w;
        }
        printf("%lld\n",sum);
    }
}
