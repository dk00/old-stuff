/*
PROB:packrec
LANG:C++
*/
#include<cstdio>
#include<algorithm>
using namespace std;
struct rect{int x,y;}s[4];
int n,mini,p[4],u[4],res[10000];
void check(int x,int y)
{
    if(x*y==mini)
        res[n++]=x;
    if(x*y<mini)
    {
        mini=x*y,n=0;
        res[n++]=x;
    }
}
void go()
{
    int i,h,w;
    int h0=s[p[0]].x,h1=s[p[1]].x,h2=s[p[2]].x,h3=s[p[3]].x,
        w0=s[p[0]].y,w1=s[p[1]].y,w2=s[p[2]].y,w3=s[p[3]].y;
    h=h0>?h1>?h2>?h3,w=w0+w1+w2+w3;
    check(h<?w,h>?w);
    h=h0+(h1>?h2>?h3),w=w0>?(w1+w2+w3);
    check(h<?w,h>?w);
    h=h0>?(h1+(h2>?h3)),w=w0+(w1>?(w2+w3));
    check(h<?w,h>?w);
    h=w=0;
    h>?=s[p[2]].x>?s[p[3]].x,w+=s[p[2]].y+s[p[3]].y;
    h+=s[p[0]].x+s[p[1]].x,w>?=s[p[0]].y>?s[p[1]].y;
    check(h<?w,h>?w);
    h=(h0+h2)>?h1,w=(w0+w1)>?(w2+w3);
    if(w2+w3<=w0)h>?=h0+h3;
    else h>?=(h0>?h1)+h3;
    if(w2>w0)h>?=(h0>?h1)+h2;
    check(h<?w,h>?w);
    /*h=(h0+h2
    check(h<?w,h>?w);*/
}
void go(int d)
{
    if(d>=4)go();
    for(int i=0;i<4;i++)
        if(u[i])
        {
            u[i]--,p[d]=i;
            go(d+1);
            swap(s[i].x,s[i].y);
            go(d+1);
            swap(s[i].x,s[i].y);
            u[i]++;
        }
}
main()
{
    freopen("packrec.in","r",stdin);
    freopen("packrec.out","w",stdout);
    int i;
    mini=2147000000;
    for(i=0;i<4;i++)
        scanf("%d %d",&s[i].x,&s[i].y),u[i]=1;
    go(0);
    printf("%d\n",mini);
    sort(res,res+n);
    for(i=0;i<n;i++)
        if(!i || res[i]!=res[i-1])
            printf("%d %d\n",res[i],mini/res[i]);
}
