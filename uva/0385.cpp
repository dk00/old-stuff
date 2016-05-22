#include<cstdio>
struct pt
{
    double x,y;
    double operator*(pt a)const{return x*a.y-y*a.x;}
    bool operator<(pt a)const{return *this*a<0;}
}s[9999];
main()
{
    int i,j,k,n,x;
    double px,py,r;
    while(~scanf("%lf %lf %lf",&px,&py,&r) && r>=0)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%lf %lf",&s[i].x,&s[i].y);
            s[i].x-=px,s[i].y-=py;
            if(s[i].x*s[i].x+s[i].y*s[i].y>r*r)
                i--,n--;
        }
        for(i=x=0;i<n;i++)
        {
            for(j=k=0;j<n;j++)
                if(s[i]*s[j]>=0)k++;
            x>?=k;
            x>?=n-k;
        }
        printf("%d\n",x);
    }
}
