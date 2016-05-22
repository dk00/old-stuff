#include<ctime>
#include<cstdio>
short sc_a0[32]={0,1,1,12,1,9,12,60,1,7,9,45,12,45,60,400,
    1,5,7,35,9,25,45,240,12,35,45,180,60,240,400,10000},
    sc_a1[19683],sc_a2[19683],
    p5[5][5]={{0,1,1,1,0},{1,1,1,0,1},{1,1,0,1,1},
        {1,0,1,1,1},{1,1,1,1,1}},
    q5[5]={1,2,3,4,5},
    p6[5][6]={{0,1,0,1,1,0},{0,1,1,0,1,0},{2,1,1,1,1,0},
        {0,1,1,1,1,2},{0,1,1,1,1,0}},
    q6[5]={6,7,8,9,10},
    ta[177147][11],tb[177147][11],tc[177147][11];

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
void proc(int u,int s[])
{
    int i,j,k,l,n=0;
    short tmp;
    for(i=1;i<6;i++)        //s+i
        for(j=0;j<5;j++)    //p5,p6
            for(k=0;k<5;k++)
            {
                if(!p5[j][k])continue;
                p5[j][k]=0;
                for(l=0;l<5 && (s[i+l]==p5[j][l]);l++);
                if(l>=5)
                ta[u][n]=i+k,tb[u][n++]=q5[j];
                p5[j][k]=1;
            }
    for(i=0;i<6;i++)
      for(j=0;j<5;j++)    //p5,p6
            for(k=0;k<6;k++)
            {
                if(!p6[j][k])continue;
                tmp=p6[j][k],p6[j][k]=0;
                for(l=0;l<6 && (s[i+l]==p6[j][l]);l++);
                if(l>=6)
                ta[u][n]=i+k,tb[u][n++]=q6[j];
                p6[j][k]=tmp;
            }
    ta[u][n]=-1;
    if(n>=11)
        putchar('!');
    /*if(u%729>=486)tmp=486;
    else if(u%729>=243)tmp=243;
    else return;
    for(i=0;i<n;i++)
        for(j=0;i<n && ta[u-tmp][j]>=0;j++)
        {
            if(ta[u][i]==ta[u-tmp][j] && tb[u][i]==tb[u-tmp][j])
            {
                ta[u][i]=ta[u][n-1],tb[u][i]=tb[u][n-1];
                ta[u][--n]=-1,j=0;
            }
        }
    for(i=0;i<n;i++)tc[u][i]=0;
    for(j=0;ta[u-tmp][j]>=0;j++)
    {
        for(i=0;i<n;i++)
            if(ta[u][i]==ta[u-tmp][j] && tb[u][i]==tb[u-tmp][j])
                break;
        if(i>=n)
        {
            ta[u][n]=ta[u-tmp][j],tb[u][n]=tb[u-tmp][j];
            tc[u][n++]=1;
        }
    }
    ta[u][n]=-1;*/
}
void setscore()
{
    int i,j,k,tmp[15],last,now;
    now=-1;
    for(i=0;i<19683;i++)
    {
        for(j=0,k=i;j<9;j++,k/=3)
            tmp[j]=k%3;
        for(j=0;j<5;j++)
        {
            last=now,now=calc_a1(tmp+j);
            sc_a1[i]+=now;
            if(last==400 && now==400)
            sc_a1[i]+=5000;
        }
        if(i%243>161)
            sc_a2[i]=sc_a1[i]-sc_a1[i-162];
        else if(i%243>80)
            sc_a2[i]=sc_a1[i]-sc_a1[i-81];
    }
    i=157494;
        for(j=0,k=i;j<11;j++,k/=3)
            tmp[j]=k%3;
        proc(i,tmp);
    i=157737;
        for(j=0,k=i;j<11;j++,k/=3)
            tmp[j]=k%3;
        proc(i,tmp);
    for(i=0;i<177147;i++)
    {
        for(j=0,k=i;j<11;j++,k/=3)
            tmp[j]=k%3;
        proc(i,tmp);
    }
}
main()
{
    printf("%d\n",time(NULL));
    setscore();
    int i,k;
    short *pos,*type;
    char s[100],name[][7]={"","_ooo_","ooo_o","oo_oo","o_ooo",
    "ooooo","_o_oo_","_oo_o_","xoooo_","_oooox","_oooo_"};
    int tmp[11]={0,0,0,0,0,0,0,1,1,0,0};
    while(scanf("%s",s)!=EOF)
    {
        for(i=11,k=0;i>=0;i--)
        {
            k*=3;
            if(s[i]=='o')k+=1;
            else if(s[i]=='x')k+=2;
        }
        printf("%d\n",k);
        printf("score: %d\n",sc_a2[(k/3)%19683]);
        pos=ta[k],type=tb[k];
        printf("threat(s):");
        for(i=0;pos[i]>=0;i++)
        {
            if(tc[k][i])printf(" del");
            else printf(" add");
            printf(" %d(%s)",pos[i],name[type[i]]);
        }
        if(!i)printf(" (none)");
        puts("");
    }
}
