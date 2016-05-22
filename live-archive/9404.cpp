#include<cstdio>
struct pair
{
    int st,iv;
}test[1000],path[18],best[18];
int n,tn,s[60],num[1000];
void go(int d,int p)
{
    if(d>=n)return;
    int i,j,k,now,sum;
    for(i=0;s[i]==0 && i<60;i++)sum+=s[i];
    if(i>=60)
    {
        if(d<n)
            for(i=0,n=d;i<d;i++)
                best[i]=path[i];
        return;
    }
    for(now=0,q=p;sum>0 && q<tn && d+now<n;q++,now++)
        if(fit(q))
            sum-=num[q];
    if(d+now>=n)return;
    for(;p<tn;p++)
        if(fit(p))
        {
            use(p);
            go(d+1,p+1);
            unuse(p);
        }
}
main()
{
    int i,j;
    scanf("%d",&n);
    for(i=0;i<60;i++)
        s[i]=0;
    while(n--)
    {
        scanf("%d",&i);
        s[i]++;
    }
    for(j=1,n=17,tn=0;j<60;j++)
        for(i=0;i<j && i+j<60;i++)
        {
            for(k=i,l=0;s[k]==0 && k<60;k+=j,l++);
            if(k>=60)
            {
                num[tn]=l;
                test[tn++]=(pair){i,j};
            }
        }
    go(0,0);
    for(i=0;i<n;i++)
        printf("%d %d\n",best[i].st,best[i].iv);
}
