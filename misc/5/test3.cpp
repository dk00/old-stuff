#include<cstdio>
short sc_a0[32]={0,1,1,12,1,9,12,60,1,7,9,45,12,45,60,400,
      1,5,7,35,9,25,45,240,12,35,45,180,60,240,400,10000},
      sc_a1[19683];
int calc_a1(int tmp[])
{
    short i,k;
    for(i=k=0;i<5;i++)
    {
        if(tmp[i]==2)
            return 0;
        k=k*2+tmp[i];
    }
    return sc_a0[k];
}
void setscore()
{
    int i,j,k,tmp[10];
    for(i=0;i<19683;i++)
    {
        for(j=0,k=i;j<9;j++,k/=3)
            tmp[j]=k%3;
        for(j=0;j<5;j++);
            sc_a1[i]+=calc_a1(tmp+j);
    }
}
main()
{
    int n;
    setscore();
    while(scanf("%d",&n)==1)
        printf("%d\n",sc_a1[n]);
}
