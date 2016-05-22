#include<ctime>
#include<cstdlib>
int _r(int n)
{
    int i,p=0;
    for(i=0;i<5;i++)
        p=p*2+n%2;
    return p;
}
struct scoretable
{
    int sc1[8][16],sc2[8][16],sc3[15][64],sc4[15][64],sc0[2];
    void rev()
    {
        int i,j,tmp;
        for(i=0;i<4;i++)
            for(j=0;j<16;j++)
            {
                tmp=sc1[i][j],sc1[i][j]=sc1[7-i][j],sc1[7-i][j]=tmp;
                tmp=sc2[i][j],sc1[i][j]=sc2[7-i][j],sc2[7-i][j]=tmp;
            }
        for(i=0;i<15;i++)
            for(j=0;j<32;j++)
            {
                tmp=sc3[i][j],sc3[i][j]=sc3[i][_r(j)],sc3[i][_r(j)]=tmp;
                tmp=sc4[i][j],sc4[i][j]=sc4[i][_r(j)],sc4[i][_r(j)]=tmp;
            }
    }
    void gentable()
    {
        srand(time(0));
        int i,j;
        for(i=0;i<8;i++)
            for(j=0;j<16;j++)
            {
                sc1[i][j]=rand()&0xF;
                sc2[i][j]=rand()&0xF;
            }
        for(i=0;i<15;i++)
            for(j=0;j<64;j++)
            {
                sc3[i][j]=rand()&0xF;
                sc4[i][j]=rand()&0xF;
            }
        sc0[0]=50;
        sc0[1]=500;
    }
    int calc(char map[][8],int pl=1)
    {
        int i,j,k,num,sum=0;
        for(i=0;i<8;i++)
        {
            for(j=1-i%2,num=0;j<8;j++,j++)
            {
                num=(num<<1)+(map[i][j]==pl || map[i][j]==pl+2);
                if(map[i][j]==pl)
                    sum+=sc0[0];
                else if(map[i][j]==pl+2)
                    sum+=sc0[1];
                    
            }
            sum+=sc1[i][num];
        }
        for(j=0;j<8;j++)
        {
            for(j=1-i%2,num=0;j<8;j++,j++)
                num=(num<<1)+(map[i][j]==pl || map[i][j]==pl+2);
            sum+=sc2[j][num];
        }
        for(i=-7;i<=7;i++)
        {
            for(num=0,j=(0>?(-i));j<8 && i+j<8;j++)
                num=(num<<1)+(map[i+j][j]==pl || map[i-j][j]==pl+2);
            sum+=sc3[i+7][num];
            for(num=0,j=7<?(i+7);i-j+7<8 && j>=0;j--)
                num=(num<<1)+(map[i-j+7][j]==pl||map[i-j+7][j]==pl+2);
            sum+=sc4[i+7][num];
        }
        if(pl==1)
            return sum-calc(map,2);
        return sum;
    }
    void load(int n)
    {
        char f[1000];
        int i,j;
        sprintf(f,"%d",n);
        FILE *o=fopen(f,"r");
        fscanf(o,"%d %d\n",&sc0[0],&sc0[1]);
        for(i=0;i<8;i++)
            for(j=0;j<16;j++)
                fscanf(o,"%d ",&sc1[i][j]);
        for(i=0;i<8;i++)
            for(j=0;j<16;j++)
                fscanf(o,"%d ",&sc2[i][j]);
        for(i=0;i<15;i++)
            for(j=0;j<64;j++)
                fscanf(o,"%d ",&sc3[i][j]);
        for(i=0;i<15;i++)
            for(j=0;j<64;j++)
                fscanf(o,"%d ",&sc4[i][j]);
        fclose(o);
    }
    void write(int s)
    {
        char f[1000];
        int i,j;
        sprintf(f,"%d",s);
        FILE *o=fopen(f,"w");
        fprintf(o,"%d %d\n",sc0[0],sc0[1]);
        for(i=0;i<8;i++)
        {
            for(j=0;j<16;j++)
                fprintf(o,"%d ",sc1[i][j]);
            fprintf(o,"\n");
        }
        for(i=0;i<8;i++)
        {
            for(j=0;j<16;j++)
                fprintf(o,"%d ",sc2[i][j]);
            fprintf(o,"\n");
        }
        for(i=0;i<15;i++)
        {
            for(j=0;j<64;j++)
                fprintf(o,"%d ",sc3[i][j]);
            fprintf(o,"\n");
        }
        for(i=0;i<15;i++)
        {
            for(j=0;j<64;j++)
                fprintf(o,"%d ",sc4[i][j]);
            fprintf(o,"\n");
        }
        fclose(o);
    }
};
