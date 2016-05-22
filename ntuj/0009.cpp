#include<cstdio>
template<class x>inline void swap(x& a,x& b){x t=a;a=b;b=t;}
struct pt
{
    int x,y;
    void operator+=(pt a){x+=a.x,y+=a.y;}
    void operator-=(pt a){x-=a.x,y-=a.y;}
    int operator*(pt a){return x*a.y-a.x*y;}
}s[99];
main()
{
    int i,j,n;
    for(n=0;scanf("%d %d",&s[n].x,&s[n].y)==2;n++);
    for(i=1;i<n;i++)
        s[i]-=s[0];
    for(i=1;i<n;i++)
        for(j=1;j<n;j++)
            if(s[j-1]*s[j]<0)
                swap(s[j-1],s[j]);
    for(i=1;i<n;i++)
        s[i]+=s[0];
    for(i=0;i<n;i++)
        printf("(%d,%d)\n",s[i].x,s[i].y);
}
