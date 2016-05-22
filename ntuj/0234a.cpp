#include<queue>
#include<cstdio>
using namespace std;
struct day
{
    int pr,num;
    bool operator<(day x)const{return pr>x.pr;}
};
main()
{
    priority_queue<day> s;
    int i,j,k,n,T;
    long long sum;
    scanf("%d",&T);
    while(T--)
    {
        while(s.size())s.pop();
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i>k)
                s.push((day){0,i-k});
            i<?=k;
            k-=i;
            while(s.size() && k)
            {
                day tmp=s.top();
                if(tmp.pr>=j)break;
                s.pop();
                if(tmp.num>k)
                {
                    tmp.num-=k;
                    i+=k;
                    s.push(tmp);
                    k=0;
                }
                else
                    i+=tmp.num,k-=tmp.num;
            }
            s.push((day){j,i});
        }
        sum=0;
        while(s.size())
        {
            //printf("%d %d\n",s.top().pr,s.top().num);
            sum+=1ll*s.top().pr*s.top().num;
            s.pop();
        }
        printf("%lld\n",sum);
    }
}
