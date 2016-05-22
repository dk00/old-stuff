//board.h
#ifndef BORAD_H5
#define BOARD_H5
struct pattern
{
    unsigned char n,len;
    char p[8];
    int sc[226][5];
}pat[100];
const int tmax=1594323;
short sc0[tmax];
pt th[tmax][10],bl[tmax][10];
void load_data()
{
    int i,l;
    int j,k;
    FILE *fp=fopen("5_score.txt","r");
    if(!fp)
    {
        allegro_message("Can't load data");
        return;
    }
    for(i=0;i<tmax;i++)
    {
        fscanf(fp,"%d",&sc0[i]);
        th[i][0]=(pt){-1,-1};
        bl[i][0]=(pt){-1,-1};
    }
    fclose(fp);
    fp=fopen("5_table.txt","r");
    while(fscanf(fp,"%d",&i)==1)
    {
        for(l=0;fscanf(fp,"%d %d",&j,&k) && j+k>=0;l++)
            th[i][l]=(pt){j,k};
        th[i][l]=(pt){-1,-1};
        for(l=0;fscanf(fp,"%d %d",&j,&k) && j+k>=0;l++)
            bl[i][l]=(pt){j,k};
        bl[i][l]=(pt){-1,-1};
    }
    fclose(fp);
}
class Board
{
    int sc[226][2];
    short n,pn,*ns1,*pl1,flag[2];
    short pre[15][15];
    char s[15][15];
    pt move[225];
    Screen *xout;
    Input *xin;
    void check(char x,char y,char pl)
    {
        short i,j;
        if(focus((pt){x,y})==0)
            focus+=(pt){x,y};
        focus-=(pt){x,y};
        for(i=0;i<4;i++)
        {
            j=0;
            for(setter a(x,y,i);a(s)==s[x][y];++a,j++);
            for(setter a(x,y,i);a(s)==s[x][y];--a,j++);
            if(j-1>=5)
                flag[pl]=1;
        }
        if(flag[0]+flag[1])return;
        for(i=0;i<8;i++)
        {
            setter a(x,y,i);
            ++a;
            if(focus(a.topt())==0 && a(s)==0)
                focus+=a.topt();
        }
        int num1,num2,tmp7;
        for(short p=0;p<2;p++)
            for(i=0;i<4;i++)
            {
                num1=num2=0;
                setter a(x,y,i);
                a+=6;
                for(j=0;j<13;j++,--a)
                {
                    num1*=3;
                    if(a(s)==p+1)
                        num1+=1;
                    else if(a(s))
                        num1+=2;
                }
                if(p==pl)num2=num1-729;
                else num2=num1-1458;
                sc[*ns1][p]+=sc0[num1]-sc0[num2];
                //allegro_message("%d %d",num1,num2);
                a.x=x,a.y=y,a-=6;
                tmp7=bl4[!p].n;
                for(j=0;th[num1][j].x>=0;j++)
                    (*list[th[num1][j].y-2+5*p])+=a[th[num1][j].x];
                for(j=0;th[num2][j].x>=0;j++)
                    (*list[th[num2][j].y-2+5*p])-=a[th[num2][j].x];
                for(j=0;bl[num1][j].x>=0;j++)
                    (*list[bl[num1][j].y+5*!p])+=a[bl[num1][j].x];
                for(j=0;bl[num2][j].x>=0;j++)
                    (*list[bl[num2][j].y+5*!p])-=a[bl[num2][j].x];
                if(bl4[!p].n<tmp7)
                    bnum4[*ns1][!p]--;
                if(bl4[!p].n>tmp7)
                    bnum4[*ns1][!p]++;
            }
    }
public:
    xlist focus,th3[2],th4[2],th5[2],bl4[2],bl5[2];
    xlist *list[17];
    int scoret[15][15];
    bool fwts[2];
    short bnum4[225][2];
    Board(Input *in1,Screen *out,short *ns2,short * pl2):
        xin(in1),xout(out),ns1(ns2),pl1(pl2)
    {
        n=15;
        xout->setmap(s);
        list[0]=&focus,list[1]=&th3[0],list[2]=&th4[0],
        list[3]=&th5[0],list[4]=&bl4[0],list[5]=&bl5[0],
        list[6]=&th3[1],list[7]=&th4[1],list[8]=&th5[1],
        list[9]=&bl4[1],list[10]=&bl5[1];
        clear();
        focus+=(pt){7,7};
    }
    void clear()
    {
        sc[*ns1][0]=sc[*ns1][1];
        xout->print(572,170,"%6d:%6d",sc[*ns1][0],sc[*ns1][1]);
        int i,j;
        *ns1=0,flag[0]=flag[1]=0;
        bnum4[0][0]=bnum4[0][1]=0;
        for(i=0;i<11;i++)
            list[i]->clear();
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                s[i][j]=0,xout->draw(i,j);
        focus+=(pt){7,7};
        fwts[0]=fwts[1]=0;
    }
    inline bool end(){return(flag[0]+flag[1]);}
    inline bool win(int pl){return flag[pl];};
    inline bool put(short x,short y,short pl,bool draw=1)
    {
        if(!vl(x,y) || s[x][y]|| end())
            return 0;
        move[(*ns1)++]=(pt){x,y};
        s[x][y]=pl+1;
        for(int i=0;i<11;i++)
            ++(*list[i]);
        sc[*ns1][0]=sc[*ns1-1][0],sc[*ns1][1]=sc[*ns1-1][1];
        bnum4[*ns1][0]=bnum4[*ns1-1][0];
        bnum4[*ns1][1]=bnum4[*ns1-1][1];
        check(x,y,pl);
        if(draw)
        {
            xout->draw(x,y);
            xout->print(572,170,"%6d:%6d",sc[*ns1][0],sc[*ns1][1]);
        }
        return 1;
    }
    inline void undo(bool draw=1)
    {
        if(!*ns1)return;
        for(int i=0;i<11;i++)
            --(*list[i]);
        --(*ns1);
        s[move[*ns1].x][move[*ns1].y]=0;
        flag[0]=flag[1]=0;
        if(draw)
        {
            xout->draw(move[*ns1].x,move[*ns1].y);
            xout->print(572,170,"%6d:%6d",sc[*ns1][0],sc[*ns1][1]);
        }
    }
    inline int Board::go(int,int,short,short&,short&);
    inline short Board::makemove(short,short);
    inline bool wtss(short);
    inline pt search();
    void rectn(int);
    bool chntn(int,short);
    void write(char *name)
    {
        FILE *fp=fopen(name,"w");
        for(int i=0;i<*ns1;i++)
            fprintf(fp,"%d %d\n",move[i].x,move[i].y);
        fclose(fp);
    }
};
bool vl(int x,int y){return(x>=0 && x<15 && y>=0 && y<15);}
#endif

