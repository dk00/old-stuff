#include<set>
#include<cstdio>
#include<algorithm>
struct pa
{
    int b,n;
    bool operator<(pa a)const
    {
        return(b<a.b ||(b<=a.b && n<a.n));
    }
    bool operator==(pa a)const
    {
        return(b==a.b && n==a.n);
    }
};
main()
{
    std::set<pa> s0;
    s0.clear();
    int i,j,k;
    while(scanf("%d %d %d",&k,&i,&j))
    {
        if(k==1)
        {
            s0.insert((pa){i,j});
            printf("%d\n",s0.size());
        }
        else
            printf("%d\n",s0.count((pa){i,j}));
    }
}
