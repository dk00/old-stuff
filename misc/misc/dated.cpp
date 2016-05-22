#include<cstdio>
#include<cstring>
typedef unsigned char uc;
int cln=53;
char cla[53][10]={"群雄","英雄","霸王","輕步兵","重步兵","近衛兵","弓兵",
"弩兵","連弩兵","輕騎兵","重騎兵","親衛隊","弓騎兵","弩騎兵","連弩騎兵",
"輕砲車","重砲車","霹靂車","武道家","拳士","拳聖","賊兵","義賊","豪傑","策士",
"參謀","軍師","風水士","方術士","仙術士","道士","幻術士","妖術士","騎馬策士",
"騎馬參謀","騎馬軍師","舞孃","舞伎","巫女","西涼騎兵","黃巾賊","海盜","馴熊師"
,"馴虎師","都督","咒術師","仙人","輜重隊","糧秣隊","木人","土偶","皇帝","百姓"
};
int find(char s[][10],int n,char a[])
{
    while(n--)
        if(!strcmp(s[n],a))
            return n;
}

struct Char
{
    char name[13];
    uc u1[5],Str,Cmd,Int,Dex,Luk,hp1,hp2,mp,cl,lv,u2[4];
    void print()
    {
        printf("%-10s %2d %2d %2d %2d %2d %3d %2d %-8s %d\n",
        name,Str,Cmd,Int,Dex,Luk,hp1+hp2*256,mp,cla[cl],lv);
        for(int i=0;i<5;i++)
            printf("%d ",u1[i]);
        for(int i=0;i<4;i++)
            printf("%d ",u2[i]);
        puts("");
    }
    void scan()
    {
        int tmp;
        char tmp2[100];
        scanf("%s %d %d %d %d %d %d %d %s %d\n",
        &name,&Str,&Cmd,&Int,&Dex,&Luk,&tmp,&mp,tmp2,&lv);
        hp1=tmp&255;
        hp2=tmp/256;
        cl=find(cla,cln,tmp2);
        for(int i=0;i<5;i++)
            scanf("%d",&tmp),u1[i]=tmp;
        for(int i=0;i<4;i++)
            scanf("%d",&tmp),u2[i]=tmp;
    }
}ch[512];
struct item
{
    char name[17];
    uc type,spe,price,icon,base,sv,up,spc;
    void print()
    {
        printf("%-12s %2d %3d %3d %3d %2d %2d %3d %2d\n",
        name,type,spe,price,icon,base,sv,up,spc);
    }
    void scan()
    {
        scanf("%s %d %d %d %d %d %d %d %d",
        name,&type,&spe,&price,&icon,&base,&sv,&up,&spc);
    }
}it[256];
uc findit(char a[])
{
    uc i;
    for(i=0;i<255;i++)
        if(!strcmp(it[i].name,a))break;
    return i;
}
struct spell
{
    char name[11];
    uc type,tg,hit,eff,mp,icon,lv[53];
    void print()
    {
        printf("%-6s %X %d %X %X %2d %2d\n",name,type,tg,hit,eff,mp,icon);
        printf("%2d",lv[0]);
        for(int i=1;i<27;i++)
            printf(" %2d",lv[i]);
        puts("");
        printf("%2d",lv[27]);
        for(int i=28;i<53;i++)
            printf(" %2d",lv[i]);
        puts("");
    }
    void printx()
    {
        printf("%-6s %2d\n",name,mp);
    }
    void scan()
    {
        scanf("%s %X %d %X %X %d %d\n",name,&type,&tg,&hit,&eff,&mp,&icon);
        scanf("%d",&lv[0]);
        for(int i=1;i<27;i++)
            scanf("%d",&lv[i]);
        scanf("%d",&lv[27]);
        for(int i=28;i<53;i++)
            scanf("%d",&lv[i]);
    }
}sp[73];
struct one
{
    uc atk,def,psi,dex,luk,Str,Cmd,Int,Dex,Luk,hp1,hp2,mp,cl,lv,xp;
    uc wp,wl,wxp,ar,al,axp,sp,sl,sxp,_u[7];
    void print()
    {
        printf("%3d %3d %3d %3d %3d %2d %2d %2d %2d %2d %3d %3d %-8s %2d %2d\n",
        atk,def,psi,dex,luk,Str,Cmd,Int,Dex,Luk,hp1+hp2*256,mp,cla[cl],lv,xp);
        printf("%-11s %2d %3d %-11s %2d %3d %-11s\n",it[wp].name,wl,wxp,it[ar].name,al,axp,
        it[sp].name);
        for(int i=0;i<7;i++)
            printf("%02X ",_u[i]);
        puts("");
    }
    void scan()
    {
        int tmp1,tmp2;
        char tmp[100],tmp3[100],tmp4[100],tmp5[100],tmp6[100];
        scanf("%s",tmp);
        scanf("%d %d %d %d %d %d %d %d %d %d %d %d %s %d %d\n",
        &atk,&def,&psi,&dex,&luk,&Str,&Cmd,&Int,&Dex,&Luk,&tmp1,&mp,tmp3,&lv,&xp);
        hp1=tmp1%256,hp2=tmp1/256;
        cl=find(cla,cln,tmp3);
        scanf("%s %d %d %s %d %d %s\n",tmp4,&wl,&wxp,tmp5,&al,&axp,tmp6);
        wp=findit(tmp4);
        ar=findit(tmp5);
        sp=findit(tmp6);
        for(int i=0;i<7;i++)
            scanf("%X ",_u+i);
    }
}x[50];
char buf1[1000],buf2[6000],buf3[13000],buf4[0x14e1],buf5[20000];
void load()
{
    int i;
    FILE *fp=fopen("data.e5a","rb");
    fread(buf1,1,0x18c,fp);
    for(i=0;i<512;i++)
        fread(ch+i,sizeof(ch[0]),1,fp);
    for(i=0;i<104;i++)
        fread(it+i,sizeof(it[0]),1,fp);
    fread(buf2,1,0x1413,fp);
    for(i=0;i<73;i++)
        fread(sp+i,sizeof(sp[0]),1,fp);
    fread(buf3,12846,1,fp);
    fclose(fp);
}
void write()
{
    int i;
    freopen("data.txt","w",stdout);
    for(i=0;i<512;i++)
        ch[i].print();
    for(i=0;i<104;i++)
        it[i].print();
    for(i=0;i<73;i++)
        sp[i].print();
    freopen("CON","w",stdout);
}
void read()
{
    int i;
    freopen("data.txt","r",stdin);
    for(i=0;i<512;i++)
        ch[i].scan();
    for(i=0;i<104;i++)
        it[i].scan();
    for(i=0;i<73;i++)
        sp[i].scan();
    freopen("CON","r",stdin);
}
void save()
{
    int i;
    FILE *fp=fopen("data.E5","wb");
    fwrite(buf1,1,0x18c,fp);
    for(i=0;i<512;i++)
        fwrite(ch+i,sizeof(ch[0]),1,fp);
    for(i=0;i<104;i++)
        fwrite(it+i,sizeof(it[0]),1,fp);
    fwrite(buf2,1,0x1413,fp);
    for(i=0;i<73;i++)
        fwrite(sp+i,sizeof(sp[0]),1,fp);
    fwrite(buf3,12846,1,fp);
    fclose(fp);
}


int savn;
void loadsav()
{
    int i,j;
    char tmp[100];
    scanf("%d",&savn);
    sprintf(tmp,"d:\\game\\ekd5\\sv%02dd.e5s",savn);
    freopen(tmp,"rb",stdin);
    freopen("sav.txt","w",stdout);
    fread(buf4,1,0x14e0,stdin);
    for(i=0;i<25;i++)
    {
        printf("%-7s",ch[i].name);
        fread(x+i,sizeof(x[0]),1,stdin);
        x[i].print();
    }
    fread(buf5,1,15580,stdin);
    freopen("CON","r",stdin);
    freopen("CON","w",stdout);
}
void savesav()
{
    if(savn==-1)return;
    int i,j;
    char tmp[100];
    freopen("sav.txt","r",stdin);
    for(i=0;i<25;i++)
        x[i].scan();
    freopen("CON","r",stdin);
    scanf("%d",&savn);
    sprintf(tmp,"d:\\game\\ekd5\\sv%02dd.e5s",savn);
    freopen(tmp,"wb",stdout);
    fwrite(buf4,1,0x14e0,stdout);
    for(i=0;i<25;i++)
        fwrite(x+i,sizeof(x[0]),1,stdout);
    fwrite(buf5,1,15580,stdout);
    freopen("CON","w",stdout);
}
main()
{
    char cmd[100];
    load();
    savn=-1;
    while(scanf("%s",cmd) && cmd[0]!='e')
    {
        if(cmd[0]=='l')load();
        if(cmd[0]=='s')save();
        if(cmd[0]=='w')write();
        if(cmd[0]=='r')read();
        if(cmd[0]=='x')break;
    }
    if(cmd[0]!='x')return 0;
    strcpy(it[255].name,"無");
    while(scanf("%s",cmd) && cmd[0]!='e')
    {
        if(cmd[0]=='l')loadsav();
        if(cmd[0]=='s')savesav();
    }
}
