#include<cstdio>
int s[555][555],p[555][555];
int go(int st,int ed,int mid)
{
    return (ed-st+1)*mid+
           s[st][mid-1]+
           s[mid+1][ed];
}
main()
{
    int i,j,k,now,next,last,C=1;
    for(i=1;i<=500;i++)
        s[i][i]=0,s[i-1][i]=(i-1)*2,p[i-1][i]=i-1;
    for(j=2;j<=500;j++)
        for(i=k=1,last=-1;i+j<=500;i++)
        {
            p[i][i+j]=i;
            next=go(i,i+j,i);
            for(k=i+1;k<=i+j;k++)
            {
                now=go(i,i+j,k);
                if(now<=next)
                    next=now,p[i][i+j]=k;
            }
            s[i][i+j]=next;
            if(i>1 && p[i-1][i+j-1]>p[i][i+j])
            {
                printf("%d %d ",i,i+j);
                printf("%d %d\n",p[i-1][i+j-1],p[i][i+j]);
            }
            last=next;
        }
    for(i=1;i<20;i++)
    {
        for(j=1;j<20;j++)
        {
            if(j>=i)
                printf("%3d",p[i][j]);
            else printf("   ");
        }
        puts("");
    }
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d %d",&i,&j);
        printf("Case %d: %d\n",C++,s[j+1][i+j]);
    }
}
