/*
PROG:lines
LANG:C++
*/
#include<cstdio>
#include<algorithm>
struct vec
{
    int x,y;
    vec operator-(vec a)const{return (vec){x-a.x,y-a.y};}
    int operator*(vec a)const{return x*a.y-y*a.x;}
    bool operator<(vec a)const{return *this*a<0;}
    bool operator!=(vec a)const{return !!(*this*a);}
}s[200],t[40000];
bool cmp(vec a,vec b)
{
    if(a.x!=b.x)return a.x<b.x;
    return a.y<b.y;
}
main()
{
    freopen("lines.in","r",stdin);
    freopen("lines.out","w",stdout);
    int i,j,n,m;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&s[i].x,&s[i].y);
    for(i=m=0;i<n;i++)
        for(j=0;j<n;j++)
            if(cmp(s[i],s[j]))
                t[m++]=s[i]-s[j];
    std::sort(t,t+m);
    for(i=n=1;i<m;i++)
        if(t[i]!=t[i-1])n++;
    printf("%d\n",n);
}
