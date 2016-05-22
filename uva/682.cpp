#include<ctime>
#include<cstdio>
#include<cstdlib>
template<class t>void swap(t &a,t &b){t tmp=a;a=b;b=tmp;}
const int Max=10;
inline unsigned long long Rand()
{
    return rand()+((1llu*rand())<<15)+((1llu*rand())<<30)+((1llu*rand())<<45);
}
struct pt
{
    char x,y;
}p[99];
long long h1[1867][1861];
char h2[1867][1861];
char f,s[9][9],fn[99],sum;
unsigned long long Z[9][9],key;
void load(char &r,long long &k)
{
    r=h2[key%1867][key%1861];
    k=h1[key%1867][key%1861];
}
void save(char r)
{
    h2[key%1867][key%1861]=r+1;
    h1[key%1867][key%1861]=key;
}
void pick(char x,char y,char d,char n)
{
    char i;
    if(d)
        for(i=0;i<=n;i++)
            s[x][y+i]=0,p[f++]=(pt){x,y+i},sum--,key^=Z[x][y+i];
    else
        for(i=0;i<=n;i++)
            s[x+i][y]=0,p[f++]=(pt){x+i,y},sum--,key^=Z[x+i][y];
}
void undo(int d)
{
    while(f>fn[d])
        f--,s[p[f].x][p[f].y]=1,sum++,key^=Z[p[f].x][p[f].y];
}
struct Move
{
    char x,y,d,n;
}mo[25][333];
char go(int d)
{
    if(!sum)return 1;
    if(sum<=Max)
    {
        char res;
        long long _key;
        load(res,_key);
        if(key==_key && res)
            return res-1;
    }
    char i,j,tmp;
    int k,n=0;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if(s[i][j])
            {
                for(k=0;j+k<5 && s[i][j+k];k++)
                    mo[d][n++]=(Move){i,j,1,k};
                for(k=0;i+k<5 && s[i+k][j];k++)
                    mo[d][n++]=(Move){i,j,0,k};
                for(k=1;k<n;k++)
                    swap(mo[d][k],mo[d][rand()%k]);
                for(k=0;k<n;k++)
                {
                    pick(mo[d][k].x,mo[d][k].y,mo[d][k].d,mo[d][k].n);
                    fn[d+1]=f;
                    tmp=!go(d+1);
                    undo(d);
                    if(tmp)goto win;
                }
            }
    save(0);
    return 0;
win:
    save(1);
    return 1;
}
main()
{
    //srand(time(NULL));
    int i,j,T;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            Z[i][j]=Rand();
    scanf("%d",&T);
    while(T--)
    {
        key=0;
        for(i=sum=0;i<5;i++)
            for(j=0;j<5;j++)
            {
                scanf("%d",&s[i][j]);
                sum+=s[i][j];
                if(s[i][j])key^=Z[i][j];
            }
        if(go(0))puts("winning");
        else puts("losing");
    }
}
