#include<ctime>
#include<cstdio>
#include<cstdlib>
template<class t>void swap(t &a,t &b){t tmp=a;a=b;b=tmp;}
struct pt
{
    char x,y;
}p[99];
char f,s[9][9],fn[99],sum;
unsigned char a[4194304],b[4194304];
char load()
{
    int j=0;
    for(char i=0;i<25;i++)
        j=j*2+s[i/5][i%5];
    if(a[j/8]&(1<<(j%8)))
        return (b[j/8]&(1<<(j%8)))>>(j%8);
    return -1;
}
unsigned char save(char x)
{
    int j=0;
    for(char i=0;i<25;i++)
        j=j*2+s[i/5][i%5];
    a[j/8]|=(1<<(j%8));
    if(x)b[j/8]|=(1<<(j%8));
}
void pick(char x,char y,char d,char n)
{
    char i;
    if(d)
        for(i=0;i<=n;i++)
            s[x][y+i]=0,p[f++]=(pt){x,y+i},sum--;
    else
        for(i=0;i<=n;i++)
            s[x+i][y]=0,p[f++]=(pt){x+i,y},sum--;
}
void undo(int d)
{
    while(f>fn[d])
        f--,s[p[f].x][p[f].y]=1,sum++;
}
struct Move
{
    char x,y,d,n;
}mo[25][333];
char go(int d)
{
    if(!sum)return 1;
    char i,j,tmp;
    tmp=load();
    if(tmp>=0)return tmp;
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
    scanf("%d",&T);
    while(T--)
    {
        for(i=sum=0;i<5;i++)
            for(j=0;j<5;j++)
            {
                scanf("%d",&s[i][j]);
                sum+=s[i][j];
            }
        if(go(0))puts("winning");
        else puts("losing");
    }
}
