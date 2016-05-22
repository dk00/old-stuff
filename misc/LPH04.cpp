#include<stdio.h>
int ok,n,map[20][20];

int cut (int y,int x)
{
    int i,j;
    for(i=-2;i<=2;i++)
        for(j=-2;j<=2;j++)
            if(map[y+i][x+j]==1 && i!=0 && j!=0 )
                return 1;
    return 0;
}



int abs(int a)
{
    if(a>=0)
        return a;
    return -a;
}
void print(int i,int j)
{
    int t,q,nq;
    for(q=0;q<=n*2+1;q++){
        puts("");
        nq=abs(n-q);
        while(nq--)printf(" ");
        for(t=0;t<=n*2+1;t++){
            if(q==i && t==j)
                printf("2 ");
            else if(map[q][t]!=-1)
                printf("%d ",map[q][t]);
        }
/*            else
                printf("  ");*/
    }
    puts("");
}

void dfs(int i,int j,int p)
{
    int t,q;

    for(t=1;t<=n*2-1 ;t++)
        for(q=1;q<=n*2-1 ;q++)
            if(map[t][q]==1)
            {
                if(!cut(t,q))
                    return ;
            }


    while(i!=2*n && ok!=1)
    {
        if(map[i][j]==0)
        {
            if(map[i-1][j]+map[i+1][j]==2)
            {
                map[i-1][j]=map[i+1][j]=0,map[i][j]=1;
                dfs(i-1,j,p-1);
                map[i-1][j]=map[i+1][j]=1,map[i][j]=0;
                if(p==1 || ok==1)
                    ok=1,print(i,j);
            }
            if(map[i][j-1]+map[i][j+1]==2)
            {
                map[i][j-1]=map[i][j+1]=0,map[i][j]=1;
                dfs(i,j-1,p-1);
                map[i][j-1]=map[i][j+1]=1,map[i][j]=0;
                if(p==1 || ok==1)
                    ok=1,print(i,j);
            }
            if(map[i-1][j-1]+map[i+1][j+1]==2)
            {
                map[i-1][j-1]=map[i+1][j+1]=0,map[i][j]=1;
                dfs(i-1,j-1,p-1);
                map[i-1][j-1]=map[i+1][j+1]=1,map[i][j]=0;
                if(p==1 || ok==1)
                    ok=1,print(i,j);
            }
            j++;
        }
        else if(map[i][j]==-1)
        {
            j=0,i++;
            while(map[i][++j]==-1);
        }
        else
            j++;
        if(p==1)
            ok=1;
    }
}


main()
{
    int i,j,k,p;
    while(scanf("%d",&n)!=EOF)
    {
        for(i=0;i<20;i++)
            for(j=0;j<20;j++)
                map[i][j]=-1;

        p=0;
        for(i=1;i<=n-1;i++)
            for(j=1;j<=n+i-1;j++)
                scanf("%d",&map[i][j]),p+=(map[i][j]==1);
        for(i=1;i<=n*2-1;i++)
            scanf("%d",&map[n][i]),p+=(map[n][i]==1);
        for(i=1;i<=n-1;i++)
            for(j=i+1;j<=n*2-1;j++)
                scanf("%d",&map[i+n][j]),p+=(map[i+n][j]==1);


        dfs(0,0,p);
        if(ok) print(50,50);
        else puts("No solution.");

    }
}
