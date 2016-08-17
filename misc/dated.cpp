#include<cstdio>
#include<cstring>
typedef unsigned char uc;
int cln=53;
char cla[53][10]={"�s��","�^��","�Q��","���B�L","���B�L","��çL","�}�L",
"���L","�s���L","���M�L","���M�L","�˽ö�","�}�M�L","���M�L","�s���M�L",
"������","������","�R�E��","�Z�D�a","���h","���t","��L","�q��","����","���h",
"�ѿ�","�x�v","�����h","��N�h","�P�N�h","�D�h","�۳N�h","���N�h","�M�����h",
"�M���ѿ�","�M���x�v","�R�]","�Rɫ","�Ťk","��D�M�L","���y��","���s","�����v"
,"����v","����","�G�N�v","�P�H","������","³����","��H","�g��","�ӫ�","�ʩm"
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
}it[104];
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
char buf1[1000],buf2[6000],buf3[13000];
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
main()
{
    char cmd[100];
    load();
    while(scanf("%s",cmd) && cmd[0]!='e')
    {
        if(cmd[0]=='l')load();
        if(cmd[0]=='s')save();
        if(cmd[0]=='w')write();
        if(cmd[0]=='r')read();
    }
}
