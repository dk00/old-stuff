inline bool ab(int x,int y)
{
    return(x>=0 && x<boardsize && y>=0 && y<boardsize);
}
void newgame()
{
    int i,j,n=boardsize;
    win[0]=win[1]=0;
    ns=pl=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            map[i][j]=0,drawgrid(0,i,j);
        togo[0]=(pt){7,7};
        ged[0]=ged[1]=1;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                use[i][j]=0,ref[i][j]=-1;
            }
    use[7][7]++;
    ref[7][7]=0;
    tn[0][0]=tn[1][0]=0;
    mark(grx,gry,0);
    for(i=0;i<8;i++)
        evil[i/4][i%4].tn[0]=evil[i/4][i%4].count=0;
}
void getwin(int r)
{
    win[pl]=1;
    if(r)allegro_message("Player %d win!",pl+1);
}
void add()
{
    int i,j,x=move[ns-1].x,y=move[ns-1].y;
    for(i=0;i<4;i++)
        for(j=-2;j<=2;j++)
            if(ab(x+dx[i]*j,y+dy[i]*j) && !map[x+dx[i]*j][y+dy[i]*j]
            && !use[x+dx[i]*j][y+dy[i]*j]++)
            {
                togo[ged[ns]]=(pt){x+dx[i]*j,y+dy[i]*j};
                ref[x+dx[i]*j][y+dy[i]*j]=ged[ns]++;
            }
}
void uadd()
{
    int i,j,x=move[ns-1].x,y=move[ns-1].y;
    for(i=0;i<4;i++)
        for(j=-2;j<=2;j++)
            if(ab(x+dx[i]*j,y+dy[i]*j) && !map[x+dx[i]*j][y+dy[i]*j])
                if(!--use[x+dx[i]*j][y+dy[i]*j])
                    ref[x+dx[i]*j][y+dy[i]*j]=-1;
}
void put(int x,int y,int r,int i)
{
    if(win[pl] || win[!pl] || map[x][y])
        return;
    if(i>=0)
        x=togo[i].x,y=togo[i].y;
    move[ns++]=(pt){x,y};
    map[x][y]=pl+1;
    if(r)
        drawgrid(pl+1,x,y);
    if(count(x,y))
        getwin(r);
    pl=!pl;
    pt tmp;ns--;
    int j,lx=move[ns].x,ly=move[ns].y,n=boardsize;
    if(i<0)
    {
        i=ref[x][y];
        if(i<0)
            togo[i=ged[ns]++]=move[ns];
    }
    use[lx][ly]++;
    tmp=togo[i],togo[i]=togo[ns],togo[ns]=tmp;
    ref[togo[i].x][togo[i].y]=i;
    ref[togo[ns].x][togo[ns].y]=ns;
    gst[ns++]=i;
    ged[ns]=ged[ns-1];
    add();
    check();
    for(i=0;i<8;i++)
        evil[i/4][i%4].next();
}
void undo(int r)
{
    if(ns<1)
        return;
    pt tmp;
    uadd();
    int i=gst[--ns];
    tmp=togo[i],togo[i]=togo[ns],togo[ns]=tmp;
    ref[togo[i].x][togo[i].y]=i;
    ref[togo[ns].x][togo[ns].y]=ns;
    if(!--use[move[ns].x][move[ns].y])
        ged[ns]--;
    win[0]=win[1]=0;
    map[move[ns].x][move[ns].y]=0;
    if(r)
    {
        drawgrid(0,move[ns].x,move[ns].y);
        mark(grx+1,gry,0);
        mark(grx-1,gry,0);
    }
    pl=ns%2;
    for(i=0;i<8;i++)
        evil[i/4][i%4].prev();
}
bool count(int x=grx,int y=gry)
{
    int i,j,nx,ny,num;
    for(i=0;i<4;i++)
    {
        num=1,nx=x+dx[i],ny=y+dy[i];
        while(ab(nx,ny) && map[nx][ny]==pl+1)
            num++,nx+=dx[i],ny+=dy[i];
        nx=x-dx[i],ny=y-dy[i];
        while(ab(nx,ny) && map[nx][ny]==pl+1)
            num++,nx-=dx[i],ny-=dy[i];
        if(num>=5)
            return 1;
    }
    return 0;
}
