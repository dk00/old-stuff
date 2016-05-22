#include<cstdio>
#include<algorithm>
using namespace std;
const int D=1000000000;
struct pt
{
    long long x,y;
    bool operator<(pt a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
    pt operator-(pt a)const{return (pt){x-a.x,y-a.y};}
    long long operator*(pt a)const{return x*a.x+y*a.y;}
}s[1500],t[1500];
bool vcmp(pt a,pt b)
{
    return a.x*b.y<a.y*b.x;
}

main()
{
    int i,j,k,n,m,sum;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)
        {
            scanf("%I64d %I64d",&s[i].x,&s[i].y);
          //  s[i].x+=D,s[i].y+=D;
        }
        sort(s,s+n);
        for(i=sum=0;i<n;i++)
        {
            for(j=m=0;j<i;j++)
                t[m++]=s[j]-s[i];
            sort(t,t+m,vcmp);
            for(j=k=0;k<m;j++)
            {
                while(k<m && t[j]*t[k]>0)k++;
                if(k<m && t[j]*t[k]==0)sum++;
            }
            for(j=i+1,m=0;j<n;j++)
                t[m++]=s[j]-s[i];
            sort(t,t+m,vcmp);
            for(j=k=0;k<m;j++)
            {
                while(k<m && t[j]*t[k]>0)k++;
                if(k<m && t[j]*t[k]==0)sum++;
            }
        }
        printf("%d\n",sum);
    }
}
