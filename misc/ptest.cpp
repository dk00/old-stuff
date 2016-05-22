#include<stdio.h>
const int cn=3,h=5,w=6;
int sum;
int p[h][w];
int dfs(int nh,int nw)
{
    if(nh>=h)
        return 1;
    if(nw>=w)
        return dfs(nh+1,0);
    int sum=0;
    for(int i=0;i<cn;i++)
        if((nh==0 || i!=p[nh-1][nw]) && (nw==0 || i!=p[nh][nw-1]))
        {
            p[nh][nw]=i;
            sum+=dfs(nh,nw+1);
        }
    return sum;
}
main()
{
    printf("%d\n",dfs(0,0));
    getchar();
}
