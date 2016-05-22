#include<cstdio>
const int N=99,M=99,L=1;
/* n => team, m=> stage
c1 => team vs team
c2 => team to stage
c3 => team to time
*/
int n,m,t,c1[N][M],c2[N][M],c3[N][M],s[N][N+M][2];
void print()
{
    int i,j;
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=t;j++)
            if(s[i][j][0])
                printf("%c%c ",'A'+s[i][j][0]-1,'A'+s[i][j][1]-1);
            else
                printf("-- ");
        puts("");
    }
}
int test(int x)
{
    int i,j,k;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(c2[i][j])
            {
                for(k=1;k<=t;k++)
                {
                    if(!c3[i][k])continue;
                    if(!s[j][k][0] && x)break;
                    if(s[j][k][0] && c1[i][s[j][k][0]])break;
                }
                if(k>t)return 1;
            }
    return 0;
}
/*int go0(int i,int j,int x)
{
    if(i>n)return 1;
    //if(test(x))return 0;
    if(j>m)return go(i+1,1,x);
    print();
    int k;
    for(k=1;k<=t;k++)
    {
        if(!c3[i][k])continue;
        c3[i][k]--;
        if(!s[j][k][0])
        {
            s[j][k][0]=i;
            c2[i][j]--;
            if(x && go(i,j+1,x-1))return 1;
            c2[i][j]++;
            s[j][k][0]=0;
        }
        else if(!s[j][k][1] && c1[i][s[j][k][0]])
        {
            s[j][k][1]=i;
            c1[i][s[j][k][0]]--;
            c1[s[j][k][0]][i]--;
            c2[i][j]--;
            if(go(i,j+1,x))return 1;
            c2[i][j]++;
            c1[s[j][k][0]][i]++;
            c1[i][s[j][k][0]]++;
            s[j][k][1]=0;
        }
        c3[i][k]++;
    }
    return 0;
}*/
int go(int i,int j,int x=3)
{
    if(i>n)return 1;
    //if(test(x))return 0;
    if(j>m)return go(i+1,1,x);
    if(!c2[i][j])return go(i,j+1,x);
    int k,l;
    c2[i][j]--;
    for(k=1;k<=n;k++)
    {
        if(k==i || !c1[i][k] || !c2[k][j])continue;
        for(l=1;l<=t;l++)
            if(c3[i][l] && c3[k][l] && !s[j][l][0])break;
        if(l>t)continue;
        c1[i][k]--;
        c3[i][l]--;
        c1[k][i]--;
        c2[k][j]--;
        c3[k][l]--;
        s[j][l][0]=i;
        s[j][l][1]=k;
        if(go(i,j+1,x))return 1;
        s[j][l][0]=0;
        s[j][l][1]=0;
        c1[i][k]++;
        c3[i][l]++;
        c1[k][i]++;
        c2[k][j]++;
        c3[k][l]++;
    }
    c2[i][j]++;
    return 0;
}
main()
{
    int i,j;
    while(~scanf("%d %d",&n,&m))    
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                c1[i][j]=L;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                c2[i][j]=1;
        
        for(i=1;i<=n;i++)
            for(j=1;j<=N+M;j++)
                c3[i][j]=1;
        for(i=1;i<=m;i++)
            for(j=1;j<=N+M;j++)
                s[i][j][0]=s[i][j][1]=0;
        /*for(i=1;i<=m;i++)
            c2[1][i]=0,s[i][i][0]=1;*/
        for(t=m;!go(1,1);t++)
            printf("%d\n",t);
        print();
    }
}
