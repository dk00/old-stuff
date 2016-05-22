#include<queue>
#include<cstdio>
main()
{
    std::priority_queue<int> h;
    int i,j;
    long long sum;
    while(~scanf("%d",&i))
    {
        while(i--)
            scanf("%d",&j),h.push(-j);
        sum=0;
        while(h.size()>1)
        {
            i=-h.top();
            h.pop();
            j=-h.top();
            h.pop();
            sum+=i+j;
            h.push(-i-j);
        }
        h.pop();
        printf("%lld\n",sum);
    }
}
