#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,d0[99],d1[99],c[99],r[99];
void tran(int &x,int &y)
{
    swap(x,y);
    y=n-1-y;
}
int test(int x,int y)
{

    int i,tmp=1;
    for(i=0;i<4;i++){
        tmp&=(d0[x+y]==1 && d1[x-y+n-1]==1 && c[y]==1 && r[x]==1);
        tran(x,y);
    }
    return tmp;
}
void put(int x,int y,int z)
{
    int i,tmp=0;
    for(i=0;i<4;i++){
        d0[x+y]+=z;
        d1[x-y+n-1]+=z;
        r[x]+=z;
        c[y]+=z;
        tran(x,y);
    }
}
int ub,Max,px[99],py[99];
int go(int d)
{
    if(d>=Max)return 1;
    int i,j,sum=0;
    ub>?=d;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            put(i,j,1);
            px[d]=i;
            py[d]=j;
            if((!d || i>px[d-1] || (i==px[d-1] && j>px[d-1]))&&test(i,j))
                sum+=go(d+1);
            put(i,j,-1);
        }
    return sum;
}
main()
{
    int i,j;
    while(scanf("%d",&n)==1){
        Max=n,ub=0;
        m=(n+1)/2;
        go(0);
        Max=ub;
        printf("%d %d\n",ub,go(0));
    }
}
/*
12
3 512,512,7168,8192,16384,32768,208896,274432,

*/
