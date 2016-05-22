#include<cstdio>
int n,max,sum,s[20];
void go(int w,int i)
{
    if(w>sum/2)return;
    if(w>max)max=w;
    for(;i<n;i++)
        go(w+s[i],i+1);
}
main()
{
    int i;
    while(scanf("%d",&n)==1)
    {
        max=0;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",s+i);
            sum+=s[i];
        }
        go(0,0);
        printf("%d\n",sum-2*max);
    }
}
