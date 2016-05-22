#include<map>
#include<string>
#include<cstdio>
using namespace std;
map<string,int> tnum;
void settype()
{
    tnum["--"]=0;
    tnum["¤õ"]=1;
    tnum["¤ô"]=2;
    tnum["¯ó"]=3;
    tnum["¹p"]=4;
    tnum["¦B"]=5;
    tnum["¶W"]=6;
    tnum["Às"]=7;
    tnum["´c"]=8;
    tnum["´¶"]=9;
    tnum["®æ"]=10;
    tnum["¬r"]=11;
    tnum["¦a"]=12;
    tnum["­¸"]=13;
    tnum["ÂÎ"]=14;
    tnum["©¥"]=15;
    tnum["°­"]=16;
    tnum["¿û"]=17;
}
int getint()
{
    int x;
    scanf("%d",&x);
    return x;
}
struct pokemon
{
    char name[60];
    short n,sn,x;
    char t1,t2;
    unsigned char c[6];
    unsigned char e[6];
    char get()
    {
        char tmp[99];
        x=getint();
        n=getint();
        sn=getint();
        scanf("%s",name);
        scanf("%s",tmp);
        t1=tnum[tmp];
        scanf("%s",tmp);
        t2=tnum[tmp];
        for(int i=0;i<6;i++)c[i]=getint();
        getint();
        for(int i=0;i<6;i++)e[i]=getint();
        getint();
    }
}s;
main()
{
    int c,i=0;
    FILE* fp=fopen("pokemon.dat","wb");
    settype();
    for(i=0;i<498;i++)
    {
        s.get();
        fwrite(&s,sizeof(s),1,fp);
    }
    fclose(fp);
}
