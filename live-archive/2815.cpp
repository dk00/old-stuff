#include<cstdio>
#include<algorithm>
struct B
{
    int a,b;
    bool operator<(B x)const{return(a<x.a ||(a==x.a && b<x.b));}
}s[10001];
int p[10001];
main()
{
    int i,j,k,l,n,x;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d %d",&s[i].a,&s[i].b);
        std::sort(s,s+n);
        p[0]=s[0].b;
        for(i=x=1;i<n;i++)
        {
            for(j=0,k=x;j<=k;)
            {
                l=(j+k)/2;
                if((!l || p[l-1]<=s[i].b)&&(l==x || s[i].b<p[l]))
                    break;
                else if(!l || p[l-1]<=s[i].b)j=l+1;
                else k=l-1;
            }
            p[l]=s[i].b;
            if(l==x)x++;
        }
        printf("%d\n",x);
    }
    puts("*");
}
