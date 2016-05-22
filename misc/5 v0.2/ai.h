//ai.h
#ifndef AI_H5
#define AI_H5
pt going[300],xd[225][300],orz[225][300],tmp2[50][225];
short thn3[50][2],thn4[50][2],thn5[50][2],note[50][300];
int maxsc[50];
void Board::rectn(int d)
{
    thn3[d][0]=th3[0].n,thn4[d][0]=th4[0].n,thn5[d][0]=th5[0].n;
    thn3[d][1]=th3[1].n,thn4[d][1]=th4[1].n,thn5[d][1]=th5[1].n;
}
bool Board::chntn(int d,short pl)
{
    return(th3[pl].n>thn3[pl][d+1] || th4[pl].n>thn4[pl][d+1]
    || th5[pl].n>thn5[pl][d+1]);
}
inline short Board::makemove(short pl,short d)
{
    short i,n=0;
    note[d][0]=0;
    if(th5[pl].n)   //Winning move
    {
        tmp2[d][0]=th5[pl][0];
        return 1;
    }
    if(bl5[pl].n>1)return 0;    // Losing
    if(bl5[pl].n==1)
    {
        tmp2[d][0]=bl5[pl][0];
        return 1;
    }
    if(bl4[!pl].n)
    {
        for(i=0;i<bl4[!pl].n;i++)
            tmp2[d][i]=bl4[!pl][i];
        return bl4[!pl].n;
    }
    for(i=0;i<th4[pl].n;i++)
        note[d][n]=0,tmp2[d][n++]=th4[pl][i];
    if(bnum4[*ns1][pl]>1)return n;
    for(i=0;i<bl4[pl].n;i++)
        note[d][n]=0,tmp2[d][n++]=bl4[pl][i];
    if(bl4[pl].n)return n;
    for(i=0;i<th3[pl].n;i++)
        note[d][n]=0,tmp2[d][n++]=th3[pl][i];
    for(i=0;i<focus.n;i++)
        note[d][n]=1,tmp2[d][n++]=focus[i];
    return n;
}
short last[50];
inline int Board::go(int a,int b,short d,short& pl,short& ns)
{
    if(d+2<=Level && last[d+2] && Level-d<2 && wtss(pl))return b;
    int now=sc[ns][pl]-sc[ns][!pl];
    if(d==0)
        return sc[ns][pl]-sc[ns][!pl];
    maxsc[d]>?=now;
    /*if(last && !chntn(d,!pl))
        return a-1;*/
    short i,found=0,n=makemove(pl,d);
    now=a-1;
    rectn(d);
    for(i=0;i<n;i++)
    {
       /*if(!note[d][0] && i && note[d][i])
            return a;*/
        put(tmp2[d][i].x,tmp2[d][i].y,pl,0);
        last[d]=note[d][i];
        pl=!pl;
        if(found)
            now=-go(-a-1,-a,d-1,pl,ns);
        if(!found || a<now && now<b)
            now=-go(-b,-a,d-1,pl,ns);
        undo(0),pl=!pl;
        if(now>=b)return b;
        if(now>a)found=1,a=now;
    }
    return a;
}
inline pt Board::search()
{
    pt best;
    int now,max;
    short i,j,n,d=Level+2,&ns=*ns1,&pl=*pl1,debug=0;
    fwts[pl]=0,fwts[!pl]=1;
    if(wtss(pl))
    {
        fwts[pl]=1,fwts[!pl]=0;
        return going[ns];
    }
    dflag=0;
    n=makemove(pl,d);
    if(n)best=tmp2[d][0];
    else if(bl5[pl].n)best=bl5[pl][0];
    else if(bl4[pl].n)best=bl4[pl][0];
    //allegro_message("First: %d,%d",best.x,best.y);
    for(i=0;i<15;i++)
        for(j=0;j<15;j++)
            scoret[i][j]=0;
    max=glb-1;
    for(i=0;i<=d;i++)
        maxsc[d]=glb;
    rectn(d);
    for(i=0;i<n;i++)
    {
        put(tmp2[d][i].x,tmp2[d][i].y,pl,debug);
        //if(debug)xin->click();
        last[d]=note[d][i];
        pl=!pl;
        if(wtss(pl))
        {
            undo(debug),pl=!pl;
            //if(debug)xin->click();
            continue;
        }
        fwts[pl]=0;
        if(n>1)
            now=-go(glb,gub,Level,pl,ns);
        if(now>max)
            max=now,best=tmp2[d][i];
        if(now==max && rand()%4==0)
            best=tmp2[d][i];
        scoret[tmp2[d][i].x][tmp2[d][i].y]=now;
        undo(debug),pl=!pl;
        //if(debug)xin->click();
    }
    return best;
}
inline bool Board::wtss(short pl)
{
    bool result=0,debug=dflag;
    if(debug)xin->click();
    short start=*ns1,now;
    if(th5[pl].n>0)
    {
        going[*ns1]=th5[pl][0];
        return 1;
    }
    if(bl5[pl].n>1)return 0;
    int i,j,k,n1=0,n2=0;
    if(bl5[pl].n==0)
    {
        if(bl4[!pl].n)
            for(i=0;i<bl4[!pl].n-1;i++)
            {
                going[*ns1]=bl4[!pl][i];
                put(bl4[!pl][i].x,bl4[!pl][i].y,pl,debug);
                if(bl5[!pl].n>1)
                {
                    undo(debug);
                    return 1;
                }
                undo(debug);
            }
        for(i=0;i<th4[pl].n;i++)
            xd[*ns1][i]=th4[pl][i];
        n1=th4[pl].n;
    }
    else if(bl5[pl].n==1 && th4[pl](bl5[pl][0]))
        n1=1,xd[*ns1][0]=bl5[pl][0];
    for(i=0;i<n1;i++)
    {
        going[*ns1]=xd[*ns1][i];
        put(xd[*ns1][i].x,xd[*ns1][i].y,pl,debug);
        if(bl5[!pl].n+bnum4[*ns1][!pl]>1)
        {
            undo(debug);
            return 1;
        }
        put(bl5[!pl][0].x,bl5[!pl][0].y,!pl,debug);
        result=wtss(pl);
        while(*ns1>start)undo(debug);
        if(result)return 1;
    }
    if(bnum4[*ns1][pl]>1)return 0;
    if(th4[!pl].n)return 0;
    if(bl5[pl].n==1)
    {
        if(!bnum4[*ns1][pl] && th3[pl](bl5[pl][0]))
            n1=1,xd[*ns1][0]=bl5[pl][0];
        else return 0;
    }
    else if(bnum4[*ns1][pl]==1)
    {
        for(j=n1=0;j<bl4[pl].n;j++)
            if(th3[pl](bl4[pl][j]))
                xd[*ns1][n1++]=bl4[pl][j];
    }
    else
    {
        for(i=n1=0;i<th3[pl].n;i++)
            xd[*ns1][i]=th3[pl][i];
        n1=th3[pl].n;
    }
    for(i=0;i<n1;i++)
    {
        going[*ns1]=xd[*ns1][i];
        put(xd[*ns1][i].x,xd[*ns1][i].y,pl,debug);
        if(bnum4[*ns1][!pl]>1)
        {
            undo(debug);
            return 1;
        }
        now=*ns1;
        for(j=n2=0;j<bl4[!pl].n;j++,n2++)
            orz[now][j]=bl4[!pl][j];
        for(j=0,k=1;j<n2;j++)
            put(orz[now][j].x,orz[now][j].y,!pl,debug);
        if(debug)result=wtss(pl);
        while(*ns1>start)undo(debug);
        if(result)return 1;
    }
    return 0;
}
#endif
