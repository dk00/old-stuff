#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int Small=1;
int select(int s[],int n,int m)
{
    int i,j,k,x,n1,n2;
    if(n<Small)
    {
        for(i=0;i<m;i++)
        {
            for(j=k=i;j<n;j++)
                if(s[j]<s[k])
                    k=j;
            swap(s[i],s[k]);
        }
        return s[m];
    }
    for(i=1,j=n-1;;)
    {
        for(;i<=j && s[i]<=s[0];i++);
        for(;j>i && s[j]>s[0];j--);
        if(i<j)swap(s[i],s[j]);
        else break;
    }
    if(i==m)return s[0];
    if(i>m)return select(s+1,i-1,m);
    return select(s+i,n-i,m-i);
}
int s[1000001];
main()
{
    srand(time(NULL));
    int i,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        scanf("%d",&i);
        printf("%d\n",select(s,n,i));
    }
}
