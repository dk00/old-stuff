#include<cstdlib>
struct scoretable
{
    int sc1[8][16],sc2[8][16],sc3[15][64],sc4[15][64];
    void gentable()
    {
        srand(time(0));
        int i,j;
        for(i=0;i<8;i++)
            for(j=0;j<16;j++)
            {
                sc1[i][j]=rand()&0xFF;
                sc2[i][j]=rand()&0xFF;
            }
        for(i=0;i<15;i++)
            for(j=0;j<64;j++)
            {
                sc3[i][j]=rand()&0xFF;
                sc4[i][j]=rand()&0xFF;
            }
    }
    int calc(char map[][],int pl=1)
    {
        int i,j,k,num,sum=0;
        for(i=0;i<8;i++)
        {
            for(j=num=0;j<8;j++)
                num=num<<1+(map[i][j]==pl || map[i][j]==pl+2);
            sum+=sc1[i][num];
        }
        for(j=0;j<8;j++)
        {
            for(i=num=0;i<8;i++)
                num=num<<1+(map[i][j]==pl || map[i][j]==pl+2);
            sum+=sc2[j][num];
        }
        for(i=-7;i<=7;i++)
        {
            for(num=0,j=(-i>?0);j<8;j++)
                num=num<<1+(map[i-j][j]==pl || map[i-j][j]==pl+2);
            sum+=sc3[i+7][num];
            i+y-7=0;
            for(num=0,j=0>?i;j<8;j++)
                num=num<<1+(map[i-j][j]==pl || map[i-j][j]==pl+2);
            sum+=sc4[i+7][num];
        }
        return sum;
    }
}
