u[999][999],dx[]={1,0,-1,0},dy[]={0,1,0,-1};
valid(x,y){return!u[x][y];}
main()
{
    int i,j,n,m,k,x,y;
    scanf("%d %d %d",&n,&m,&k);
    for(i=0;i<=n;i++)
        u[i][0]=u[i][m+1]=1;
    for(i=0;i<=m;i++)
        u[0][i]=u[n+1][i]=1;
    for(x=y=1,i=0;k--;)
    {
        u[x][y]=1;
        while(i<4 && !valid(x+dx[i],y+dy[i]))i++;
        if(i>=4)
            for(i=0;i<4;i++)
                if(valid(x+dx[i],y+dy[i]))
                    break;
        if(i>=4)break;
        if(i<4)
            x+=dx[i],y+=dy[i];
        else break;
    }
    printf("%d %d\n",y-1,x-1);
}
