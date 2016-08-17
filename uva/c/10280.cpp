#include<cstdio>
#include<cstring>
#include<algorithm>
struct S
{
    int min,max;
    bool operator<(S a)const{return max-min<a.max-a.min;}
}s[100];
bool u[20300000];
main()
{
    int i,j,k,l,n,m,t,min;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&m,&n);
        memset(u,0,20300000);
        m*=1000;
        for(i=0;i<n;i++)
            scanf("%d %d",&s[i].min,&s[i].max);
        std::sort(s,s+n);
        min=m+1;
        for(i=n-1,u[0]=1;m<min && i>=0;i--)
        {
            for(j=l=0,k=s[i].min;l<s[i].min && k<=min;j++)
                if(u[j])
                {
                    if(k<j+s[i].min)
                        l=0,k=j+s[i].min;
                    while(k<=j+s[i].max || u[k]==1)
                        l++,u[k++]=1;
                }
            min=j+s[i].min;
        }
        if(m>=min ||(m<20300000 && u[m]))
            puts("0");
        else
        {
            for(i=m;i>0 && !u[i];i--);
            printf("%d\n",m-i);
        }
        if(t)puts("");
    }
}
