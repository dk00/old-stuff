#include<map>
#include<string>
#include<cstdio>
using namespace std;
map<string,int> tnum;
void settype()
{
    tnum["--"]=0;
    tnum["��"]=1;
    tnum["��"]=2;
    tnum["��"]=3;
    tnum["�p"]=4;
    tnum["�B"]=5;
    tnum["�W"]=6;
    tnum["�s"]=7;
    tnum["�c"]=8;
    tnum["��"]=9;
    tnum["��"]=10;
    tnum["�r"]=11;
    tnum["�a"]=12;
    tnum["��"]=13;
    tnum["��"]=14;
    tnum["��"]=15;
    tnum["��"]=16;
    tnum["��"]=17;
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
