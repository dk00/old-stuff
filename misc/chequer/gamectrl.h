int mx[][4]={{1,1,-1,-1},{-1,-1,1,1}},
    my[][4]={{1,-1,1,-1},{1,-1,1,-1}};
int def=2468;
inline int abs(int n){return n<0?-n:n;}
inline bool able(int x,int y)
{
    return(x>=0 && x<bh && y>=0 && y<bw && !map[x][y]);
}
inline bool able1(int x,int y)
{
    return(x>=0 && x<bh && y>=0 && y<bw);
}
inline bool able(int x1,int y1,int x2,int y2)
{
    int pl=map[x1][y1]%2;
    if(x1<0 || x1>=bh || y1<0 || y1>=bw || !map[x1][y1] ||
       x2<0 || x2>=bh || y2<0 || y2>=bw || map[x2][y2] ||
       (map[x1][y1]<4 && (1-2*pl)*(x2-x1)<0) ||
       (map[(x1+x2)/2][(y1+y2)/2]%2==pl || !map[(x1+x2)/2][(y1+y2)/2]))
        return 0;
    return 1;
}
inline void start()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            map[i][j]=0;
    map[0][1]=map[0][3]=map[0][5]=map[0][7]=2;
    map[1][0]=map[1][2]=map[1][4]=map[1][6]=2;
    map[2][1]=map[2][3]=map[2][5]=map[2][7]=2;
    map[5][0]=map[5][2]=map[5][4]=map[5][6]=3;
    map[6][1]=map[6][3]=map[6][5]=map[6][7]=3;
    map[7][0]=map[7][2]=map[7][4]=map[7][6]=3;
    movecur(3,3);
    pl=jmp[0]=jmp[1]=0,num[0]=num[1]=2468;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            jnum[i][j]=0,mark[i][j]=7,refresh(i,j);
}
inline void select()
{
    if(!map[curx][cury] || map[curx][cury]%2!=pl%2)
        return;
    if(jmp[pl] && mark[curx][cury]<71)
        return;
    if(selx==curx && sely==cury)
    {
        selx=-1;
        if(mark[curx][cury]==55)
            mark[curx][cury]=7;
        else mark[curx][cury]=71;
        for(int i=0;i<4;i++)
        {
            if(able(curx+mx[pl][i],cury+my[pl][i]))
            {
                mark[curx+mx[pl][i]][cury+my[pl][i]]=7;
                refresh(curx+mx[pl][i],cury+my[pl][i]);
            }
            if(able(curx+mx[pl][i]*2,cury+my[pl][i]*2))
            {
                mark[curx+mx[pl][i]*2][cury+my[pl][i]*2]=7;
                refresh(curx+mx[pl][i]*2,cury+my[pl][i]*2);
            }
        }
    }
    else if(selx==-1)
    {
        if(lx>=0 && (lx!=curx || ly!=cury))
            return;
        if(mark[curx][cury]==7)
            mark[curx][cury]=55;
        else mark[curx][cury]=87;
        selx=curx,sely=cury;
        for(int i=0;i<map[curx][cury]-pl;i++)
        {
            if(jmp[pl])
            {
                if(able(curx+mx[pl][i]*2,cury+my[pl][i]*2) &&
                map[curx+mx[pl][i]][cury+my[pl][i]] &&
                map[curx+mx[pl][i]][cury+my[pl][i]]%2!=pl)
                {
                    mark[curx+mx[pl][i]*2][cury+my[pl][i]*2]=39;
                    refresh(curx+mx[pl][i]*2,cury+my[pl][i]*2);
                }
            }
            else if(able(curx+mx[pl][i],cury+my[pl][i]))
            {
                mark[curx+mx[pl][i]][cury+my[pl][i]]=39;
                refresh(curx+mx[pl][i],cury+my[pl][i]);
            }
        }
    }
    refresh(curx,cury);
}
inline void check1(int x1,int y1,int x2,int y2)
{
    if(able(x1,y1,x2,y2))
    {jmp[map[x1][y1]%2]--; if(!--jnum[x1][y1])
        mark[x1][y1]=7,refresh(x1,y1);}
}
inline void check2(int x1,int y1,int x2,int y2)
{
    if(able(x1,y1,x2,y2))
        jmp[map[x1][y1]%2]++,jnum[x1][y1]++,
        mark[x1][y1]=71,refresh(x1,y1);
}
inline void check3(int x,int y,int pl)
{
    for(int i=0;i<4;i++)
        if(able(x,y,x+dx[i]*2,y+dy[i]*2))
            jnum[x][y]--,jmp[pl]--;
    mark[x][y]=7,refresh(x,y);
}
inline void check4(int x,int y,int pl)
{
    for(int i=0;i<4;i++)
        if(able(x,y,x+dx[i]*2,y+dy[i]*2))
            jnum[x][y]++,jmp[pl]++,mark[x][y]=71;
    refresh(x,y);
}
inline int sc1(int k,int x,int y)
{
    int tmp;
    if(k>=4)tmp=300;
    else if(k>0)tmp=200;
    else tmp=0;
    if(x<=0 || x>=7 || y<=0 || y>=7)
        tmp+=3;
    else for(int i=0;i<4;i++)
        if(map[x+dx[i]][y+dy[i]] && map[x+dx[i]][y+dy[i]]%2==k%2)
            tmp+=2;
    if((k%2==0 && !x)||(k%2 && x==7))
        tmp+=5;
    return tmp;
}
inline int move(int px,int py,int nx,int ny)
{
    num[pl]-=sc1(map[px][py],px,py);
    int pl=map[px][py]%2,ux,uy;
    if(abs(ux=nx-px)>1)ux/=2;
    if(abs(uy=ny-py)>1)uy/=2;
    movecur(px,py);
    select(),check3(px,py,pl);
    check1(px-ux,py-uy,px+ux,py+uy);
    check1(px-ux,py+uy,px+ux,py-uy);
    check1(px+ux,py-uy,px-ux,py+uy);
    check1(nx-ux*2,ny+uy*2,nx,ny);
    check1(nx+ux*2,ny-uy*2,nx,ny);
    check1(nx+ux*2,ny+uy*2,nx,ny);
    if((nx-px)/2)
        check1((nx+px)/2+ux,(ny+py)/2-uy,(nx+px)/2-ux,(ny+py)/2+uy),
        check1((nx+px)/2-ux,(ny+py)/2+uy,(nx+px)/2+ux,(ny+py)/2-uy),
        check3((nx+px)/2,(ny+py)/2,!pl),map[(nx+px)/2][(ny+py)/2]=0;
    map[nx][ny]=map[px][py],map[px][py]=0,mark[px][py]=7;
    movecur(nx,ny);
    if(!(map[nx][ny]&4)&&((!pl && nx==7)||(pl && !nx)))
        map[nx][ny]|=4;
    refresh((nx+px)/2,(ny+py)/2),refresh(px,py),refresh(nx,ny);
    check2(px-ux*2,py-uy*2,px,py);
    check2(px-ux*2,py+uy*2,px,py);
    check2(px+ux*2,py-uy*2,px,py);
    check2(nx-ux,ny+uy,nx+ux,ny-uy);
    check2(nx+ux,ny-uy,nx-ux,ny+uy);
    check2(nx+ux,ny+uy,nx-ux,ny-uy);
    if((nx-px)/2)
        check2((nx+px)/2+ux*2,(ny+py)/2-uy*2,(nx+px)/2,(ny+py)/2),
        check2((nx+px)/2-ux*2,(ny+py)/2+uy*2,(nx+px)/2,(ny+py)/2);
    check4(nx,ny,pl);
    num[pl]+=sc1(map[nx][ny],nx,ny);
    if((nx-px)/2 && mark[nx][ny]==71)
        {lx=nx,ly=ny;return 1;}
    lx=-1;
    return 0;
}
struct rec
{
    int lx,ly,jmp[2],jnum[18],map[2];
}test[300];
int d2,_pl[200],cx[]={1,-1,2,-2,-1,-2},cy[]={-1,1,-2,2,-1,-2};
inline void copy(int x1,int y1,int x2,int y2)
{
    int i,u,ux=x2-x1,uy=y2-y1;
    _pl[d2]=pl;
    u=(x2-x1)/2;
    if(u)ux/=2,uy/=2;
    for(i=0;i<6;i++)
    {
        if(able1(x1+ux*cx[i],y1+uy*cy[i]))
            test[d2].jnum[i]=jnum[x1+ux*cx[i]][y1+uy*cy[i]];
        if(able1(x2-ux*cx[i],y2-uy*cy[i]))
            test[d2].jnum[i+6]=jnum[x2-ux*cx[i]][y2-uy*cy[i]];
    }
    if(u)
    {
        x2=(x1+x2)/2,y2=(y1+y2)/2;
        for(i=0;i<4;i++)
            if(able1(x2-ux*cx[i],y2-uy*cy[i]))
                test[d2].jnum[i+12]=jnum[x2-ux*cx[i]][y2-uy*cy[i]];
        num[(test[d2].map[1]=map[x2][y2])%2]-=sc1(map[x2][y2],x2,y2);
        test[d2].jnum[17]=jnum[x2][y2];
    }
    test[d2].map[0]=map[x1][y1];
    test[d2].jmp[0]=jmp[0],test[d2].jmp[1]=jmp[1];
    test[d2].jnum[16]=jnum[x1][y1];
    test[d2].lx=lx,test[d2].ly=ly;
}
inline void undo(int x1,int y1,int x2,int y2)
{
    pl=_pl[d2];
    num[map[x2][y2]%2]-=sc1(map[x2][y2],x2,y2);
    map[x2][y2]=jnum[x2][y2]=0,mark[x2][y2]=7;
    int i,u,ux=x2-x1,uy=y2-y1;
    u=(x2-x1)/2;
    if(u)ux/=2,uy/=2;
    for(i=0;i<6;i++)
    {
        if(able1(x1+ux*cx[i],y1+uy*cy[i]))
            mark[x1+ux*cx[i]][y1+uy*cy[i]]=
            (jnum[x1+ux*cx[i]][y1+uy*cy[i]]=test[d2].jnum[i])?71:7;
        if(able1(x2-ux*cx[i],y2-uy*cy[i]))
            mark[x2-ux*cx[i]][y2-uy*cy[i]]=
            (jnum[x2-ux*cx[i]][y2-uy*cy[i]]=test[d2].jnum[i+6])?71:7;
    }
    if(u)
    {
        x2=(x1+x2)/2,y2=(y1+y2)/2;
        for(i=0;i<4;i++)
            if(able1(x2-ux*cx[i],y2-uy*cy[i]))
                mark[x2-ux*cx[i]][y2-uy*cy[i]]=
                (jnum[x2-ux*cx[i]][y2-uy*cy[i]]=test[d2].jnum[i+12])?71:7;
        num[(map[x2][y2]=test[d2].map[1])%2]+=sc1(test[d2].map[1],x2,y2);
        mark[x2][y2]=(jnum[x2][y2]=test[d2].jnum[17])?71:7;
    }
    map[x1][y1]=test[d2].map[0];
    num[map[x1][y1]%2]+=sc1(map[x1][y1],x1,y1);
    jmp[0]=test[d2].jmp[0],jmp[1]=test[d2].jmp[1];
    mark[x1][y1]=(jnum[x1][y1]=test[d2].jnum[16])?71:7;
    lx=test[d2].lx,ly=test[d2].ly;
}
