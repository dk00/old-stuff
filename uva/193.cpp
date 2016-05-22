#include<stdio.h>
int n,num,max,v[100],use[100],best[100],c[100][100];
void go(int p)
{
    int i;
    for(i=0;i<n;i++)
        if(c[p][i] && use[i]){
            use[i]=0;
            go(i);
            use[i]=1;
        }
    int tmp[100];
    for(i=0;i<n;i++)tmp[i]=use[i];
    v[p]=1;
    num++;
    for(i=0;i<n;i++)
        if(c[p][i])use[i]=0;
    if(num>max){
        max=num;
        for(i=0;i<n;i++)best[i]=v[i];
    }
    for(i=0;i<n;i++)
        if(use[i]){
            use[i]=0;
            go(i);
            use[i]=1;
        }
    v[p]=0;
    num--;
    for(i=0;i<n;i++)
        use[i]=tmp[i];
}
main()
{
int i,j,m,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
        {
            use[i]=1,v[i]=0;
            for(j=0;j<n;j++)
                c[i][j]=0;
        }
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            c[i][j]=c[j][i]=1;
        }
        num=max=0;
        go(0);
        printf("%d\n",max);
        for(i=0;i<n && !best[i];i++);
        printf("%d",++i);
        for(;i<n;i++)
            if(best[i])
                printf(" %d",i+1);
        puts("");
    }
}
