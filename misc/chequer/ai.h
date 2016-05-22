const int level=8,maxs=4000;
int d1,list[30][8][2];
int o[32],pos[32][2];
int _select(int sx,int sy)
{
    if(!map[sx][sy] || map[sx][sy]%2!=pl%2)
        return 0;
    if(jmp[pl] && mark[sx][sy]<71)
        return 0;
    int n=0;
    for(int i=0;i<map[sx][sy]-pl;i++)
        if(jmp[pl])
        {
            if(able(sx+mx[pl][i]*2,sy+my[pl][i]*2) &&
            map[sx+mx[pl][i]][sy+my[pl][i]] &&
            map[sx+mx[pl][i]][sy+my[pl][i]]%2!=pl)
                list[d2][n][0]=sx+mx[pl][i]*2,list[d2][n++][1]=sy+my[pl][i]*2;
        }
        else if(able(sx+mx[pl][i],sy+my[pl][i]))
            list[d2][n][0]=sx+mx[pl][i],list[d2][n++][1]=sy+my[pl][i];
    return n;
}
int _move(int px,int py,int nx,int ny)
{
    num[pl]-=sc1(map[px][py],px,py);
    int pl=map[px][py]%2,ux,uy;
    if(abs(ux=nx-px)>1)ux/=2;
    if(abs(uy=ny-py)>1)uy/=2;
    check3(px,py,pl);
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
    if(!(map[nx][ny]&4)&&((!pl && nx==7)||(pl && !nx)))
        map[nx][ny]|=4;
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
    return((nx-px)/2 && mark[nx][ny]==71);
}
int nnode,_px,_py;
int search(int alpha,int beta)
{
    ++nnode;
    if(!d1)
    {
        if(num[0]==0)
            return -maxs;
        if(num[1]==0)
            return maxs;
        return num[0]-num[1];
    }
    int i,j,k,l,m=0,tmp,max=-999,first=1;
    for(l=0;l<32;l++)
    {
        i=pos[o[l]][0],j=pos[o[l]][1];
        if(lx>=0 &&(i!=lx || j!=ly))
            continue;
        m+=(k=_select(i,j));
        while(k--)
        {
            copy(i,j,list[d2][k][0],list[d2][k][1]);
            if(!_move(i,j,list[d2][k][0],list[d2][k][1]))pl=!pl;
            if(_pl[d2]==0)
            {
                if(first)
                    d1--,d2++,tmp=search(alpha,beta),d1++,d2--;
                else
                {
                    d1--,d2++,tmp=search(alpha,alpha+1),d1++,d2--;
                    if(alpha<tmp && tmp<beta)
                        d1--,d2++,tmp=search(alpha,beta),d1++,d2--;
                }
                if((d1==level && tmp>alpha)|| bx1==-1)
                    bx1=i,by1=j,bx2=list[d2][k][0],by2=list[d2][k][1];
                if(tmp>alpha)
                    first=0;
                alpha>?=tmp;
            }
            else
            {
                if(first)
                    d1--,d2++,tmp=search(alpha,beta),d1++,d2--;
                else
                {
                    d1--,d2++,tmp=search(beta-1,beta),d1++,d2--;
                    if(alpha<tmp && tmp<beta)
                        d1--,d2++,tmp=search(alpha,beta),d1++,d2--;
                }
                if((d1==level && tmp<beta)|| bx1==-1)
                    bx1=i,by1=j,bx2=list[d2][k][0],by2=list[d2][k][1];
                if(tmp<beta)
                    first=0;
                beta<?=tmp;
            }
            undo(i,j,list[d2][k][0],list[d2][k][1]);
            if(pl==0 && alpha>=beta)
                return beta;
            if(pl && alpha>=beta)
                return alpha;
        }
    }
    if(!m)
    {
        if(pl==0)return -maxs;
        if(pl==1)return maxs;
    }
    if(pl==0)return alpha;
    return beta;
}
int search_init()
{
    int i,j,k,n,m,max,tmp[100][4];
    _px=22;
    if(!pl)_py=27;else _py=40;
    nnode=0;
    print(_px,_py,7,"%7s"," ");
    for(n=0;n<20;n++)
    {
        i=rand()%32,j=rand()%32;
        k=o[i],o[i]=o[j],o[j]=k;
    }
    bx1=-1;
    _refresh=0;
    /*for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            for(k=0;k<64;k++)
                _sc[i][j][k/8][k%8]=-1000*m;*/
    d1=level,d2=0;
    search(-maxs,maxs);
    _refresh=1;
    print(_px,_py,7,"%7d",nnode);
    return max;
}
void ai_init()
{
    int i,j,k;
    for(i=k=0;i<8;i++)
        for(j=1-i%2;j<8;j++,j++)
            pos[k][0]=i,pos[k][1]=j,o[k]=k++;
}
void calc()
{
    for(int i=num[0]=num[1]=0;i<8;i++)
        for(int j=1-i%2;j<8;j++,j++)
        if(map[i][j])
            num[map[i][j]%2]+=sc1(map[i][j],i,j);
}
