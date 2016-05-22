#include<algorithm>
using namespace std;
const int N=100000;
typedef int D;
D r[20][N];
void init(int n,D s[])
{
    for(j=0;j<n;j++)
        r[0][j]=s[j];
    for(i=k=1;k<n;i++,k*=2)
        for(j=0;j+k<n;j++)
            r[i][j]=max(r[i-1][j],r[i-1][j+k]);
}
D query(int l,int r)
{
    if(l>r)swap(l,r);
    int d=r-l,v=r[0][l];
    for(i=0,k=1;k<=d;i++,k*=2)
        if(k&d)
        {
            v=max(v,r[i][l]);
            d-=k,l+=k;
        }
    return v;
}
