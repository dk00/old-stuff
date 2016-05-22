/*
#1
{0,1,1,12,1,9,12,60,1,7,9,45,12,45,60,400,
    1,5,7,35,9,25,45,240,12,35,45,180,60,240,400,10000}
#2
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,10000}
*/
short sc_a0[32]={0,1,1,10,1,10,10,100,1,10,10,100,10,100,100,1000,
    1,10,10,100,10,100,100,1000,10,100,100,1000,100,1000,1000,10000},
    p5[5][5]={{0,1,1,1,0},{1,1,1,0,1},{1,1,0,1,1},
        {1,0,1,1,1},{1,1,1,1,1}},
    q5[5]={0,1,1,1,3},
    p6[5][6]={{0,1,0,1,1,0},{0,1,1,0,1,0},{2,1,1,1,1,0},
        {0,1,1,1,1,2},{0,1,1,1,1,0}},
    q6[5]={0,0,1,1,2},
    sc_a1[19684],sc_a2[19684],sc_b0[]={100,300,1000,2000},
    ta[177148][20],tb[177148][20],tc[177148][20],tt[177148][20];

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
    int i,j,k,l,n=0,tmp;
    for(i=1;i<6;i++)        //s+i
        for(j=0;j<5;j++)    //p5,p6
            for(k=0;k<5;k++)
            {
                if(!p5[j][k])continue;
                p5[j][k]=0;
                for(l=0;l<5 && (s[i+l]==p5[j][l]);l++);
                if(l>=5)
                tt[u][n]=j+1,ta[u][n]=i+k,tb[u][n++]=q5[j];
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
                tt[u][n]=j+6,ta[u][n]=i+k,tb[u][n++]=q6[j];
                p6[j][k]=tmp;
            }
    ta[u][n]=-1;
    if(u%729>=486)tmp=486;
    else if(u%729>=243)tmp=243;
    else return;
    for(i=0;i<n;i++)
        for(j=0;i<n && ta[u-tmp][j]>=0;j++)
        {
            if(ta[u][i]==ta[u-tmp][j] && tt[u][i]==tt[u-tmp][j])
            {
                ta[u][i]=ta[u][n-1],tb[u][i]=tb[u][n-1],
                tt[u][i]=tb[u][n-1];ta[u][--n]=-1,j=0;
            }
        }
    for(i=0;i<n;i++)tc[u][i]=0;
    for(j=0;ta[u-tmp][j]>=0;j++)
    {
        for(i=0;i<n;i++)
            if(ta[u][i]==ta[u-tmp][j] && tt[u][i]==tt[u-tmp][j])
                break;
        if(i>=n)
        {
            ta[u][n]=ta[u-tmp][j],tb[u][n]=tb[u-tmp][j],
            tt[u][n]=tt[u-tmp][j];
            tc[u][n++]=1;
        }
    }
    ta[u][n]=-1;
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
    for(i=0;i<177147;i++)
    {
        for(j=0,k=i;j<11;j++,k/=3)
            tmp[j]=k%3;
        proc(i,tmp);
    }
}
const short inf=30000;
void check()
{
    sc[0][ns]=sc[0][ns-1],sc[1][ns]=sc[1][ns-1];
    short i,j,x=move[ns-1].x,y=move[ns-1].y,*s1,*s2,*s3,tmp[4];
    int k,l;
    for(i=0;i<4;i++)
    {
        for(j=-5,k=l=0;j<=5;j++)
        {
            k*=3,l*=3;
            if(ab(x+dx[i]*j,y+dy[i]*j))
            {
                if(map[x+dx[i]*j][y+dy[i]*j])
                    k+=(map[x+dx[i]*j][y+dy[i]*j]==2)+1,
                    l+=(map[x+dx[i]*j][y+dy[i]*j]==1)+1;
            }
            else k+=2,l+=2;
        }
        for(j=0;j<4;j++)tmp[j]=0;
        sc[0][ns]+=sc_a2[(k/3)%19683];
        sc[1][ns]+=sc_a2[(l/3)%19683];
        s1=ta[k],s2=tb[k],s3=tc[k];
        for(j=0;s1[j]>-1;j++)
            if(s3[j])
                evil[0][s2[j]].del(x+dx[i]*(5-s1[j]),y+dy[i]*(5-s1[j]));
            else
                evil[0][s2[j]].ins(x+dx[i]*(5-s1[j]),y+dy[i]*(5-s1[j]));
        s1=ta[l],s2=tb[l],s3=tc[l];
        for(j=0;s1[j]>-1;j++)
            if(s3[j])
                evil[1][s2[j]].del(x+dx[i]*(5-s1[j]),y+dy[i]*(5-s1[j]));
            else
                evil[1][s2[j]].ins(x+dx[i]*(5-s1[j]),y+dy[i]*(5-s1[j]));
    }
}
int nnode[10],npv[10];
short go(short,short,short);
bool pv[20];
inline short score()
{
    int i,j,num=sc[pl][ns]-sc[!pl][ns];
    for(i=3;i>=0 && evil[pl][i].npt()==0;i--);
    for(j=3;j>=0 && evil[!pl][j].npt()==0;j--);
    if(i>j)
        while(i>j)
            num+=evil[pl][i--].npt()*sc_b0[i];
    if(i<j)
        while(i<j)
            num-=evil[!pl][j--].npt()*sc_b0[j];
    return (short)num;
}
void next(short &a,short &b,short &d)
{
    short tmp;
    put(move[ns].x,move[ns].y,0,-1);
    if(pv[d])
    {
        npv[d]++;
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
        pv[d]=1;
    }
    undo(0);
}
bool test(short& a,short& b,short& d,pt s[],int n)
{
    for(int j=n-1;j>=0;j--)
    {
        if(map[s[j].x][s[j].y])
            continue;
        move[ns]=s[j];
        next(a,b,d);
        if(a>=b)return 1;
    }
    return 0;
}
short go(short a,short b,short d)
{
    nnode[d]++;
    pv[d]=0;
    if(evil[pl][3].npt())
    {
        if(d==Level)
            Best=evil[pl][3].s[0];
        return inf-sc[!pl][ns];
    }
    if(evil[!pl][3].npt())
    {
        if(d==Level)
            Best=evil[!pl][3].s[0];
        if(evil[!pl][3].npt()>1)
            return sc[pl][ns]-inf;
        if(d==0)
            return score();
        test(a,b,d,evil[!pl][3].s,evil[!pl][3].npt());
        return a;
    }
    if(evil[pl][2].npt())
    {
        if(d==Level)
            Best=evil[pl][2].s[0];
        return inf-sc[!pl][ns];
    }
    if(evil[!pl][2].npt())
    {
        if(d==0)
        {
            if(evil[!pl][2].npt()>2)
                return sc[pl][ns]-inf;
            if(evil[pl][2].npt()==2)
            {
                pt a=evil[!pl][2].s[0],b=evil[!pl][2].s[1];
                if((a.x!=b.x && abs(a.x-b.x)!=3) ||
                (a.y!=b.y && abs(a.y-b.y)!=3))
                    return sc[pl][ns]-inf;
            }
            return score();
        }
        if(test(a,b,d,evil[!pl][2].s,evil[!pl][2].npt()))
            return a;
        if(!evil[pl][1].npt())
            return a;
    }
    if(d==0)
        return score();
    for(int i=1;i>=0;i--)
    if(evil[pl][i].npt())
        if(test(a,b,d,evil[pl][i].s,evil[pl][i].npt()))
            return a;
    for(int i=1;i>=0;i--)
    if(evil[!pl][i].npt())
        if(test(a,b,d,evil[!pl][i].s,evil[!pl][i].npt()))
            return a;
    for(int i=ns;i<ged[ns];i++)
    {
        move[ns]=togo[i];
        next(a,b,d);
        if(a>=b)
            return a;
    }
    return a;
}
short search()
{
    return go(-inf,inf,Level);
}
