#ifndef hex_game_h
#define hex_game_h
const char __num[13][13]=
{
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1, 0, 1, 2, 3, 4,-1,-1,-1,-1,-1,-1},
    {-1,-1, 5, 6, 7, 8, 9,10,-1,-1,-1,-1,-1},
    {-1,-1,11,12,13,14,15,16,17,-1,-1,-1,-1},
    {-1,-1,18,19,20,21,22,23,24,25,-1,-1,-1},
    {-1,-1,26,27,28,29,30,31,32,33,34,-1,-1},
    {-1,-1,-1,35,36,37,38,39,40,41,42,-1,-1},
    {-1,-1,-1,-1,43,44,45,46,47,48,49,-1,-1},
    {-1,-1,-1,-1,-1,50,51,52,53,54,55,-1,-1},
    {-1,-1,-1,-1,-1,-1,56,57,58,59,60,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
};
extern const char *_num[13],**num;
const char adj1[61][7]={
{1,6,5,-1,0,0,0},{2,7,6,0,-1,0,0},{3,8,7,1,-1,0,0},{4,9,8,2,-1,0,0},
{10,9,3,-1,0,0,0},{6,12,11,0,-1,0,0},{7,13,12,1,0,5,-1},{8,14,13,2,1,6,-1},
{9,15,14,3,2,7,-1},{10,16,15,4,3,8,-1},{17,16,4,9,-1,0,0},
{12,19,18,5,-1,0,0},{13,20,19,6,5,11,-1},{14,21,20,7,6,12,-1},
{15,22,21,8,7,13,-1},{16,23,22,9,8,14,-1},{17,24,23,10,9,15,-1},
{25,24,10,16,-1,0,0},{19,27,26,11,-1,0,0},{20,28,27,12,11,18,-1},
{21,29,28,13,12,19,-1},{22,30,29,14,13,20,-1},{23,31,30,15,14,21,-1},
{24,32,31,16,15,22,-1},{25,33,32,17,16,23,-1},{34,33,17,24,-1,0,0},
{27,35,18,-1,0,0,0},{28,36,35,19,18,26,-1},{29,37,36,20,19,27,-1},
{30,38,37,21,20,28,-1},{31,39,38,22,21,29,-1},{32,40,39,23,22,30,-1},
{33,41,40,24,23,31,-1},{34,42,41,25,24,32,-1},{42,25,33,-1,0,0,0},
{36,43,27,26,-1,0,0},{37,44,43,28,27,35,-1},{38,45,44,29,28,36,-1},
{39,46,45,30,29,37,-1},{40,47,46,31,30,38,-1},{41,48,47,32,31,39,-1},
{42,49,48,33,32,40,-1},{49,34,33,41,-1,0,0},{44,50,36,35,-1,0,0},
{45,51,50,37,36,43,-1},{46,52,51,38,37,44,-1},{47,53,52,39,38,45,-1},
{48,54,53,40,39,46,-1},{49,55,54,41,40,47,-1},{55,42,41,48,-1,0,0},
{51,56,44,43,-1,0,0},{52,57,56,45,44,50,-1},{53,58,57,46,45,51,-1},
{54,59,58,47,46,52,-1},{55,60,59,48,47,53,-1},{60,49,48,54,-1,0,0},
{57,51,50,-1,0,0,0},{58,52,51,56,-1,0,0},{59,53,52,57,-1,0,0},
{60,54,53,58,-1,0,0},{55,54,59,-1,0,0,0},
},adj2[61][13]={
{2,7,13,12,11,-1,0,0,0,0,0,0,0},{3,8,14,13,12,5,-1,0,0,0,0,0,0},
{4,9,15,14,13,6,0,-1,0,0,0,0,0},{10,16,15,14,7,1,-1,0,0,0,0,0,0},
{17,16,15,8,2,-1,0,0,0,0,0,0,0},{7,13,20,19,18,1,-1,0,0,0,0,0,0},
{8,14,21,20,19,11,2,-1,0,0,0,0,0},{9,15,22,21,20,12,3,0,5,-1,0,0,0},
{10,16,23,22,21,13,4,1,6,-1,0,0,0},{17,24,23,22,14,2,7,-1,0,0,0,0,0},
{25,24,23,15,3,8,-1,0,0,0,0,0,0},{13,20,28,27,26,6,0,-1,0,0,0,0,0},
{14,21,29,28,27,18,7,1,0,-1,0,0,0},{15,22,30,29,28,19,8,2,1,0,5,11,-1},
{16,23,31,30,29,20,9,3,2,1,6,12,-1},{17,24,32,31,30,21,10,4,3,2,7,13,-1},
{25,33,32,31,22,4,3,8,14,-1,0,0,0},{34,33,32,23,4,9,15,-1,0,0,0,0,0},
{20,28,36,35,12,5,-1,0,0,0,0,0,0},{21,29,37,36,35,26,13,6,5,-1,0,0,0},
{22,30,38,37,36,27,14,7,6,5,11,18,-1},{23,31,39,38,37,28,15,8,7,6,12,19,-1},
{24,32,40,39,38,29,16,9,8,7,13,20,-1},{25,33,41,40,39,30,17,10,9,8,14,21,-1},
{34,42,41,40,31,10,9,15,22,-1,0,0,0},{42,41,32,10,16,23,-1,0,0,0,0,0,0},
{28,36,43,19,11,-1,0,0,0,0,0,0,0},{29,37,44,43,20,12,11,-1,0,0,0,0,0},
{30,38,45,44,43,35,21,13,12,11,18,26,-1},
{31,39,46,45,44,36,22,14,13,12,19,27,-1},
{32,40,47,46,45,37,23,15,14,13,20,28,-1},
{33,41,48,47,46,38,24,16,15,14,21,29,-1},
{34,42,49,48,47,39,25,17,16,15,22,30,-1},{49,48,40,17,16,23,31,-1,0,0,0,0,0},
{49,41,17,24,32,-1,0,0,0,0,0,0,0},{37,44,50,28,19,18,-1,0,0,0,0,0,0},
{38,45,51,50,29,20,19,18,26,-1,0,0,0},{39,46,52,51,50,43,30,21,20,19,27,35,-1},
{40,47,53,52,51,44,31,22,21,20,28,36,-1},
{41,48,54,53,52,45,32,23,22,21,29,37,-1},
{42,49,55,54,53,46,33,24,23,22,30,38,-1},{55,54,47,34,25,24,23,31,39,-1,0,0,0},
{55,48,25,24,32,40,-1,0,0,0,0,0,0},{45,51,56,37,28,27,26,-1,0,0,0,0,0},
{46,52,57,56,38,29,28,27,35,-1,0,0,0},{47,53,58,57,56,50,39,30,29,28,36,43,-1},
{48,54,59,58,57,51,40,31,30,29,37,44,-1},
{49,55,60,59,58,52,41,32,31,30,38,45,-1},{60,59,53,42,33,32,31,39,46,-1,0,0,0},
{60,54,34,33,32,40,47,-1,0,0,0,0,0},{52,57,45,37,36,35,-1,0,0,0,0,0,0},
{53,58,46,38,37,36,43,-1,0,0,0,0,0},
{54,59,56,47,39,38,37,44,50,-1,0,0,0},{55,60,57,48,40,39,38,45,51,-1,0,0,0},
{58,49,41,40,39,46,52,-1,0,0,0,0,0},
{59,42,41,40,47,53,-1,0,0,0,0,0,0},{58,52,45,44,43,-1,0,0,0,0,0,0,0},
{59,53,46,45,44,50,-1,0,0,0,0,0,0},
{60,54,47,46,45,51,56,-1,0,0,0,0,0},{55,48,47,46,52,57,-1,0,0,0,0,0,0},
{49,48,47,53,58,-1,0,0,0,0,0,0,0},
};

struct pt
{
    char x,y;
    pt operator+(pt a)const{return(pt){x+a.x,y+a.y};}
    void operator+=(pt a){x+=a.x,y+=a.y;}
    pt operator-(pt a)const{return(pt){x-a.x,y-a.y};}
    void operator-=(pt a){x-=a.x,y-=a.y;}
    bool operator==(pt a)const{return(x==a.x && y==a.y);}
};
inline char num0(pt a){return num[a.x][a.y];}
const int Npos=61;
const pt d[19]=
{
    {0,0},{0,1},{1,1},{1,0},{-1,0},{-1,-1},{0,-1},
    {0,2},{1,2},{2,2},{2,1},{2,0},{1,-1},
    {-1,1},{-2,0},{-2,-1},{-2,-2},{-1,-2},{0,-2}
},
pos[61]=
{
    {0,0},{0,1},{0,2},{0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{2,0},
    {2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{3,0},{3,1},{3,2},{3,3},{3,4},{3,5},
    {3,6},{3,7},{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8},{5,1},
    {5,2},{5,3},{5,4},{5,5},{5,6},{5,7},{5,8},{6,2},{6,3},{6,4},{6,5},{6,6},
    {6,7},{6,8},{7,3},{7,4},{7,5},{7,6},{7,7},{7,8},{8,4},{8,5},{8,6},{8,7},{8,8}
};

class hex
{
    int frm,fn[999];
    char act[999],pi[999];
    char add(char,char,char rec=1);
    void del(char,char rec=1);
    void flip(char,char rec=1);
public:
    int step,spc,cn[3],jn[3];
    char s[61],sn[3],copy[3][61],jmp[3][61],pl;
    void reset();
    char &operator[](pt p){return s[num[p.x][p.y]];}
    char &operator[](char i){return s[i];}
    char end();
    virtual char move(char p,char q,char ch=1);
    char move(pt p,char di=0,char ch=1)
    {
        if(di>6)
            return move(num0(p),num0(p+d[di]),ch);
        return move(num0(p+d[di]),num0(p+d[di]),ch);
    }
    virtual char taste(char p);
    char taste(pt p,char di){return taste(num0(p+d[di]));}
    virtual char undo();
    void copyto(char a[9][9]);
    void operator=(const char a[9][9])const;
};

#endif
