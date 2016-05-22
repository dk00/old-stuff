#include<cstdio>
#include<algorithm>
using namespace std;
#include"libmedium.h"
int s[101],p[101];
inline int medium(int a,int b,int c,int d)
{return Medium(a+1,b+1,c+1,d+1);}
void go(int x[])
{
    int i,j,tmp[5]={
        medium(x[1],x[2],x[3],x[4]),
        medium(x[0],x[2],x[3],x[4]),
        medium(x[0],x[1],x[3],x[4]),
        medium(x[0],x[1],x[2],x[4]),
        medium(x[0],x[1],x[2],x[3])};
    for(i=j=0;i<5 && j<5;i++)
        for(j=0;j<5;j++)
            if(i!=j && tmp[i]==tmp[j])
                break;
    sort(tmp,tmp+5);
    s[x[i-1]]=tmp[1]+tmp[3]-tmp[2];
}
main()
{
    int i,j,n;
    n=Init();
    for(i=0;i<n;i++)p[i]=i,s[i]=-1;
    while(n>=5)
    {
        for(i=0;i+4<n;i+=5)
            go(p+i);
        for(i=j=0;i<n;i++)
            if(s[p[i]]==-1)
                p[j++]=p[i];
        n=j;
    }
    Solution(s);
}
