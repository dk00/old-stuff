void start()
{   pl=step=0;
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
            map[i][j]=0,mark[i][j]=7;
    refresh();
}
int go(int x,int y,int mx,int my,int p)
{
    if(x>=0 && x <15 && y>=0 && y<15 && map[x][y]==p)
        return 1+go(x+mx,y+my,mx,my,p);
    return 0;
}
bool check5(int x,int y)
{
    return(go(x,y,1,0,map[x][y])+go(x,y,-1,0,map[x][y])>5 ||
           go(x,y,0,1,map[x][y])+go(x,y,0,-1,map[x][y])>5 ||
           go(x,y,1,1,map[x][y])+go(x,y,-1,-1,map[x][y])>5 ||
           go(x,y,1,-1,map[x][y])+go(x,y,-1,1,map[x][y])>5);
}
short ln,v[225][2];
void add(short x,short y)
{
    int i,j;
    for(i=-2;i<=2;i++)
    {
        if(!i)continue;
        if(able(x+i,y) && !mark[x+i][y]++)
            v[ln][0]=x+i,v[ln++][1]=y;
        if(able(x,y+i) && !mark[x][y+i]++)
            v[ln][0]=x,v[ln++][1]=y+i;
        if(able(x+i,y+i) && !mark[x+i][y+i]++)
            v[ln][0]=x+i,v[ln++][1]=y+i;
        if(able(x+i,y-i) && !mark[x+i][y-i]++)
            v[ln][0]=x+i,v[ln++][1]=y-i;
    }
}
void rem(short x,short y)
{
    int i,j;
    for(i=-2;i<=2;i++)
    {
        if(!i)continue;
        if(able(x+i,y))--mark[x+i][y];
        if(able(x,y+i))--mark[x][y+i];
        if(able(x+i,y+i))--mark[x+i][y+i];
        if(able(x+i,y-i))--mark[x+i][y-i];
    }
}
int move(bool r=true,int k=-1)
{
    oln[step]=ln;
    if(k<0)
        for(k=0;k<ln;k++)
            if(v[k][0]==curx && v[k][1]==cury)
                break;
    if(k>=ln)
        v[ln][0]=curx,v[ln++][1]=cury;
    ov[step]=k;
    swap(v[k][0],v[step][0]);
    swap(v[k][1],v[step][1]);
    list[step++]=(S){curx,cury};
    map[curx][cury]=pl+1;
    add(curx,cury);
    if(r)refresh(curx,cury);
    if(check5(curx,cury))
        return 3;
    /*if(check4tr(curx,cury))
        return 2;
    if(check3tr(curx,cury))
        return 1;*/
    return 0;
}
int move(int k)
{
    oln[step]=ln;
    ov[step]=k;
    list[step]=(S){v[k][0],v[k][1]};
    add(v[k][0],v[k][1]);
}
void undo()
{
    if(!step)return;
    step--;
    int x=list[step].x,y=list[step].y,tmp;
    rem(x,y);
    map[x][y]=0;
    swap(p[ov[step]][0],p[step][0]);
    swap(p[ov[step]][1],p[step][1]);
    ln=oln[step];
}
