/*
- possible five
- possible four threats
- possible three threats
- uncomplete threats

*/
short pt1[][5]={{0,1,1,1,0},{1,1,1,0,1},{1,1,0,1,1},{1,0,1,1,1}},
      pt2[][6]={{0,1,1,0,1,0},{0,1,0,1,1,0},
                {2,1,1,1,1,0},{0,1,1,1,1,2},{0,1,1,1,1,0}};
int table[177147];
short calc(char s[11])
{
    int i,j,k,u,tmp[6];
    short sum=0;
    for(i=0;i<5;i++)tmp[i]=2;
    for(i=1;i<9;i++)
    {
        for(j=0;j<4;j++)tmp[j]=tmp[j-1];
        tmp[j]=s[i];
        for(k=0;k<4;k++)
        {
            for(j=u=0;u>=0 && j<5;j++)
            {
                if(pt1[k][j]!=1 && pt1[k][j]!=tmp[j])u=-1;
                else if((pt2[k][j]==1 && tmp[j]==2)u=-1;
                else if(tmp[j]==pt1[k][j])u++;
            }
            if(u>0)
                sum+=sc1[k][u];
        }
    }
    for(i=0;i<6;i++)tmp[i]=2;
    for(i=0;i<11;i++)
    {
        for(j=0;j<5;j++)tmp[j]=tmp[j-1];
        tmp[j]=s[i];
        for(k=0;k<5;k++)
        {
            for(j=u=0;u>=0 && j<6;j++)
            {
                if(pt2[k][j]!=1 && pt2[k][j]!=tmp[j])u=-1;
                else if(pt2[k][j]==1 && tmp[j]==2)u=-1;
                else if(pt2[k][j]==tmp[j])u++;
            }
            if(u>0)
                sum+=sc2[k][u];
        }
    }
    return sum;
}
void pre_calc()
{
    char tmp[12];
    for(i=177146;i>=0;i--)
    {
        for(j=0;j<11;j++)
            tmp[j]=i%3,i/=3;
        table[i]=calc(tmp);
    }
}
short calc(short x,short y,short dx,short dy)
{
    int i,num=0;
    x-=dx*5,y-=dy*5;
    for(i=0;i<11;i++)
        if(x<0 || x>=15 || y<0 || y>=15)
            num=num*3+2;
        else if(!map[x][y])num*=3;
        else num=num*3+(map[x][y]==pl)+1;
    return table[num];
}
short search(short alpha,short beta)
{
    if(d==0)
        return score[step-1];
        
}
short search_init()
{

}
