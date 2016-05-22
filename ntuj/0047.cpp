#include<cmath>
#include<cstdio>
const int n=16;
struct C
{
    int r,g,b;
    double operator-(C x)const
    {
        return (r-x.r)*(r-x.r)+(g-x.g)*(g-x.g)+(b-x.b)*(b-x.b);
    }
}s[20],t;
main()
{
    int i,j;
    for(i=0;i<n;i++)
        scanf("%d %d %d",&s[i].r,&s[i].g,&s[i].b);
    while(scanf("%d %d %d",&t.r,&t.g,&t.b) && t.r>=0)
    {
        for(i=1,j=0;i<n;i++)
            if(t-s[i]<t-s[j])
                j=i;
        printf("(%d,%d,%d) maps to (%d,%d,%d)\n",t.r,t.g,t.b,s[j].r,s[j].g,s[j].b);
    }
}
