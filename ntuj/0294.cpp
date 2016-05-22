#include<cstdio>
struct rect
{
    double x1,y1,x2,y2;
    rect operator+(rect a){return(rect){x1>?a.x1,y1>?a.y1,x2<?a.x2,y2<?a.y2};}
    double operator()(){return (x2-x1)*(y2-y1);}
}s[100];
double go(int i,rect x)
{
    double sum=x();
    if(sum<=0)return 0;
    for(;i>=0;i--)
        sum-=go(i-1,x+s[i]);
    return sum;
}
main()
{
    int i,n;
    double sum;
    while(scanf("%d",&n) && n)
    {
        for(sum=i=0;i<n;i++)
        {
            scanf("%lf %lf %lf %lf",&s[i].x1,&s[i].y1,&s[i].x2,&s[i].y2);
            sum+=go(i-1,s[i]);
        }
        printf("Test case #1\nTotal explored area: %.2lf\n",sum);
    }
}
