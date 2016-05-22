#include<cstdio>
bool notp[1000001];
int p[400000];
main()
{
    int i,j,n;
    p[0]=2;
    for(n=1,i=3;i<1000001;i++,i++)
    {
        notp[i-1]=1;
        if(notp[i])continue;
        for(j=i*3;j<1000001;j+=i*2)
            notp[j]=1;
        p[n++]=i;
    }
    notp[2]=0;
    while(scanf("%d",&j) && j)
    {
        printf("%d:\n",j);
        for(i=0;p[i]<=j/2;i++)
            if(!notp[j-p[i]])
            {
                printf("%d+%d\n",p[i],j-p[i]);
                break;
            }
        if(p[i]>j/2)
            puts("NO WAY!");
    }
}
