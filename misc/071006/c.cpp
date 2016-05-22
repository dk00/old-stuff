#include<cstdio>
#include<algorithm>
struct pt
{
    int x,y;
    bool operator<(pt a)const{return x<a.x ||(x==a.x && y<a.y);}
}s[1001];
int n;
inline char find(pt a)
{
    int i,j,k;
    for(i=0,j=n-1;i<=j;)
    {
        k=(i+j)/2;
        if(s[k]<a)i=k+1;
        else if(a<s[k])j=k-1;
        else return 1;
    }
    return 0;
}
inline char find(pt a,pt b)
{
    int x0=-a.x+b.x,y0=-a.y+b.y;
    if((x0+y0)%2)return 0;
    return(find((pt){a.x+(x0+y0)/2,a.y+(y0-x0)/2}) &&
           find((pt){a.x+(x0-y0)/2,a.y+(y0+x0)/2}));
}
main()
{
    int i,j,k;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d %d",&s[i].x,&s[i].y);
        std::sort(s,s+n);
        for(i=k=0;i<n;i++)
            for(j=0;j<i;j++)
                if(find(s[i],s[j]))k++;
        printf("%d\n",k/2);
    }
}
