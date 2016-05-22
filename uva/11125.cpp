#include<cstdio>
int u[4],s[4096][4][4];
int gnum()
{
    int i,j,k;
    for(i=j=0,k=1;i<4;i++,k*=8)
        j+=k*u[i];
    return j;
}
int go(int l1,int l2)
{
    int i,j,k,l,o=gnum();
    if(s[o][l1][l2]>0)
        return s[o][l1][l2];
    s[o][l1][l2]=0;
    u[l1]-=l2;
    if(!gnum())
    {
        u[l1]+=l2;
        return 1;
    }
    for(k=0;k<4;k++)
        for(l=1;l<4 && l<=u[k];l++)
            if(k!=l1 && l!=l2)
                s[o][l1][l2]+=go(k,l);
    u[l1]+=l2;
    return s[o][l1][l2];
}
main()
{
    int i,j,k,n,T,sum;
    for(k=0;k<4096;k++)
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                s[k][i][j]=-1;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            s[0][i][j]=0;
    s[0][0][0]=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=j=0;i<n;i++)
            scanf("%d",&u[i]);
        for(i=sum=0;i<n;i++)
            for(j=1;j<=u[i];j++)
                sum+=go(i,j);
        printf("%d\n",sum);
    }
}
