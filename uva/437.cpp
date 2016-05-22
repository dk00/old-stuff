#include<stdio.h>
long x[901],y[901],z[901],t;
void sort1(int s,int e){
    if(s>=e)return;
    int p1=s+1,p2=e;
    while(1){
        for(;p1<=e && y[s]>=y[p1];p1++);
        for(;p2>s && y[s]<=y[p2];p2--);
        if(p1>=p2)break;
        t=x[p1];x[p1]=x[p2];x[p2]=t;
        t=y[p1];y[p1]=y[p2];y[p2]=t;
        t=z[p1];z[p1]=z[p2];z[p2]=t;
    }
    t=x[s];x[s]=x[p2];x[p2]=t;
    t=y[s];y[s]=y[p2];y[p2]=t;
    t=z[s];z[s]=z[p2];z[p2]=t;
    sort1(s,p2-1);
    sort1(p1,e);
}
void sort2(int s,int e){
    if(s>=e)return;
    int p1=s+1,p2=e;
    while(1){
        for(;p1<=e && x[s]>=x[p1];p1++);
        for(;p2>s && x[s]<=x[p2];p2--);
        if(p1>=p2)break;
        t=x[p1];x[p1]=x[p2];x[p2]=t;
        t=y[p1];y[p1]=y[p2];y[p2]=t;
        t=z[p1];z[p1]=z[p2];z[p2]=t;
    }
    t=x[s];x[s]=x[p2];x[p2]=t;
    t=y[s];y[s]=y[p2];y[p2]=t;
    t=z[s];z[s]=z[p2];z[p2]=t;
    sort2(s,p2-1);
    sort2(p1,e);
}
main(){
long n,i,j,ht[10000],max,C=1;
while(scanf("%ld",&n) && n){
    n*=6;
    for(i=0;i<n;i+=6){
        scanf("%ld %ld %ld",&x[i],&y[i],&z[i]);
        x[i+1]=x[i];
        y[i+1]=z[i];
        z[i+1]=y[i];
        x[i+2]=y[i];
        y[i+2]=x[i];
        z[i+2]=z[i];
        x[i+3]=y[i];
        y[i+3]=z[i];
        z[i+3]=x[i];
        x[i+4]=z[i];
        y[i+4]=x[i];
        z[i+4]=y[i];
        x[i+5]=z[i];
        y[i+5]=y[i];
        z[i+5]=x[i];
    }
    sort1(0,n-1);
    sort2(0,n-1);
    for(i=0;i<n;i++)ht[i]=z[i];
    for(i=n-1;i>=0;i--){
        for(j=n-1;j>=0;j--){
            if(x[i]<x[j] && y[i]<y[j]){
                ht[i]=ht[i]>(z[i]+ht[j])?ht[i]:(z[i]+ht[j]);
            }
        }
    }
    for(max=i=0;i<n;i++)max>?=ht[i];
    printf("Case %ld: maximum height = %ld\n",C++,max);
}
}
