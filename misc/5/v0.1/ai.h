short sc_a0[32]={0,1,1,12,1,9,12,60,1,7,9,45,12,45,60,400,
      1,5,7,35,9,25,45,240,12,35,45,180,60,240,400,10000},
      sc_a1[19683];
short thr_0[8][6]={{0,1,1,1,0,-1},{0,1,1,0,1,0},{0,1,0,1,1,0},
      {0,1,1,1,1,2},{2,1,1,1,1,0,},{1,0,1,1,1,-1},{1,1,1,0,1,-1},
      {1,1,0,1,1,-1}},thr_1[8][3]={{0,4,-1},{3,0,5},{2,0,5},{0,-1,-1},
      {4,-1,-1},{1,-1,-1},{3,-1,-1},{2,-1,-1}},
      thr_stat[19683],thr_soln[19683][3];

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
void solve(int n,int s[])
{
    int i,j,k;
    for(i=0;i<3;i++)
        thr_soln[n][i]=-1;
    for(i=0;i<8;i++)
        for(j=0;j<5;j++)
        {
            for(k=0;k<6 && thr_0[i][k]>=0;k++)
                if(thr_0[i][k]!=s[j+k])
                    break;
            if(k>=6 || thr_0[i][j]<0)
            {
                thr_stat[n]+=1*(i<3?1:3);
                for(k=0;k<3;k++)
                    thr_soln[n][k]=thr_1[i][k];
            }
        }
}
void setscore()
{
    int i,j,k,tmp[10],last,now;
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
        solve(i,tmp);
    }
}
const short inf=30000;
void check()
{
    sc[0][ns]=sc[0][ns-1],sc[1][ns]=sc[1][ns-1];
    int i,j,k,x=move[ns-1].x,y=move[ns-1].y;
    for(i=0;i<4;i++)
    {
        for(j=-4,k=0;j<=4;j++)
        {
            if(ab(x+dx[i]*j,y+dy[i]*j))
            {
                if(map[x+dx[i]*j][y+dy[i]*j])
                    k=k*3+(map[x+dx[i]*j][y+dy[i]*j]==pl+1)+1;
                else k*=3;
            }
            else k=k*3+2;
        }
        sc[!pl][ns]+=sc_a1[k]-sc_a1[k-81];
        for(j=-4,k=0;j<=4;j++)
        {
            if(ab(x+dx[i]*j,y+dy[i]*j))
            {
                if(map[x+dx[i]*j][y+dy[i]*j])
                    k=k*3+(map[x+dx[i]*j][y+dy[i]*j]!=pl+1)+1;
                else k*=3;
            }
            else k=k*3+2;
        }
        sc[pl][ns]+=sc_a1[k]-sc_a1[k-162];
    }
}
short go(short,short,short);
bool pv[20];
void next(short &a,short &b,short &d)
{
    short tmp;
    if(pv[d])
    {
        tmp=-go(-a-1,-a,d-1);
        if(a<tmp && tmp<b)
            tmp=-go(-b,-a,d-1);
    }else tmp=-go(-b,-a,d-1);
    if(d==Level)
        c_score[move[ns-1].x][move[ns-1].y]=tmp;
    if(tmp>a)
    {
        if(d==Level)
            Best=move[ns-1];
        a=tmp;
    }
}
short go(short a,short b,short d)
{
    if(sc[!pl][ns]>=10000)
        return 1-inf;
    if(d==0)
        return sc[pl][ns]-sc[1-pl][ns];
    pv[d]=0;
    for(int i=ns;i<ged[ns];i++)
    {
        put(togo[i].x,togo[i].y,0,i);
        check();
        if(d==Level && win[!pl])
            Best=move[ns-1],a=b;
        else
            next(a,b,d);
        undo(0);
        if(a>=b)
            return a;
    }
    return a;
}
short search()
{
    return go(-inf,inf,Level);
}
