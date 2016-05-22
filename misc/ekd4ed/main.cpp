#include<cstdio>
#include<cstdlib>
#include<cstring>
char buf[50000];
typedef unsigned char uc;
char name[256][20],type[256][20],item[256][20],skill[256][20],att[256][20];
int size;
unsigned find(char s[255][20],char *a)
{
    unsigned i;
    for(i=0;i<255;i++)
        if(!strcmp(s[i],a))
            break;
    return i;
}
struct data
{
    uc join,atk,def,intt,luk;
    uc hp1,hp2;
    uc sp,hit,dex,ty,lv,exp,wp,it[8],sk[8],at[8];
    uc unknow[8];
    void read(FILE *fp)
    {
        char tmp1[20],tmp2[20],tmp3[20],tmp4[20],tmp5[20],tmp6[20],tmp7[20];
        short thp;
        unsigned x1,x2,x3,x4,x5,x6;
        fscanf(fp,"%s %u",tmp2,&x1);
        join=x1;
        fscanf(fp,"%s %s %u.%u %s %d %s %u %s %u %s %u",
        tmp1,tmp3,&x1,&x2,tmp4,&x3,tmp5,&x4,tmp6,&x5,tmp7,&x6);
        lv=x1,exp=x2,sp=x4,atk=x5,def=x6,
        hp1=x3%256,hp2=x3/256;
        ty=find(type,tmp1);
        fscanf(fp," %s %u %s %u %s %u %s %u",
        tmp2,&x1,tmp2,&x2,tmp2,&x3,tmp2,&x4);
        intt=x1,hit=x2,dex=x3,luk=x4;
        fscanf(fp,"%u",&x1),wp=x1;
        for(int i=0;i<8;i++)
        {
            fscanf(fp,"%s ",tmp1);
            it[i]=find(item,tmp1);
        }
        for(int i=0;i<8;i++)
        {
            fscanf(fp,"%s ",tmp1);
            sk[i]=find(skill,tmp1);
        }
        for(int i=0;i<8;i++)
        {
            fscanf(fp,"%s ",tmp1);
            at[i]=find(att,tmp1);
        }
        for(int i=0;i<8;i++)
        {
            fscanf(fp,"%u ",&x1);
            unknow[i]=x1;
        }
    }
    void print(FILE *fp)
    {
        fprintf(fp,"%u ",join);
        fprintf(fp,"%s LV %2u.%02u HP %3u SP %3u\nAtk %3u Def %3u",
        type[ty],lv,exp,hp1+hp2*256,sp,atk,def);
        fprintf(fp," Int %3u Hit %3u Dex %3u Luk %3u\n",intt,hit,dex,luk);
        fprintf(fp,"%u ",wp);
        for(int i=0;i<8;i++)
            fprintf(fp,"%s ",item[it[i]]);
        fprintf(fp,"\n");
        for(int i=0;i<8;i++)
            fprintf(fp,"%s ",skill[sk[i]]);
        fprintf(fp,"\n");
        for(int i=0;i<8;i++)
            fprintf(fp,"%s ",att[at[i]]);
        fprintf(fp,"\n");
        for(int i=0;i<8;i++)
            fprintf(fp,"%u ",unknow[i]);
        fprintf(fp,"\n");
        fprintf(fp,"\n");
    }
}s[1000];
void write(FILE *fp)
{
    if(!fp)return;
    fseek(fp,0x1369,SEEK_SET);
    for(int i=0;i<185;i++)
        fwrite(s+i,1,sizeof(s[0]),fp);
}
void write(FILE *fp1,FILE *fp2)
{
    if(!fp1 || !fp2)return;
    fread(buf,1,0x1369,fp1);
    fwrite(buf,1,0x1369,fp2);
    for(int i=0;i<185;i++)
    {
        fread(buf,1,sizeof(s[0]),fp1);
        fwrite(s+i,1,sizeof(s[0]),fp2);
    }
    fread(buf,1,size-0x1369-0x2e*185,fp1);
    fwrite(buf,1,size-0x1369-0x2e*185,fp2);
}
void edit()
{
    int k;
    scanf("%d",&k);
    printf("%s\n",name[k]);
    s[k].print(stdout);
}
void showusage()
{
    puts("EKD4 savedata  convertor\n");
    puts("SAVFILE TXTFILE\t\tConvert savedata to text");
    puts("TXTFILE SAVFILE\t\tConvert text to savedata");
    puts("Copyleft ($) DarkKnight 2007.01, 2009.06");
}
main(int an,char **arg)
{
    int i,tmp;
    FILE *fp,*wp;
    char cmd[1000],fname[1000];
    fp=fopen("name.txt","r");
    for(i=0;fscanf(fp,"%s",name[i])==1;i++);
    fclose(fp);
    fp=fopen("item0.txt","r");
    for(i=0;fscanf(fp,"%s",item[i])==1;i++);
    fclose(fp);
    fp=fopen("skill.txt","r");
    for(i=0;fscanf(fp,"%s",skill[i])==1;i++);
    fclose(fp);
    fp=fopen("att.txt","r");
    for(i=0;fscanf(fp,"%s",att[i])==1;i++);
    fclose(fp);
    fp=fopen("type.txt","r");
    for(i=0;fscanf(fp,"%s",type[i])==1;i++);
    fclose(fp);
    item[255][0]=skill[255][0]=att[255][0]='x';
    if(an<2){
        showusage();
        return 0;
    }
    arg[0]=arg[2];
    if(an<3)arg[0]="out.txt";
    i=strlen(arg[1]);
    if(an<3 || !stricmp(arg[1]+i-4,".e4s")){
        puts("convert savedata to text");
        if(!(fp=fopen(arg[1],"rb"))){
            printf("Can't open file");
            return 0;
        }
        fseek(fp,0,SEEK_END),size=ftell(fp);
        fseek(fp,0x1369,SEEK_SET);
        wp=fopen(arg[0],"w");
        for(i=0;i<185;i++)
        {
            fread(s+i,sizeof(data),1,fp);
            fprintf(wp,"%s\n",name[i]);
            s[i].print(wp);
        }
        fclose(wp);
        fclose(fp);
//        system(arg[0]);
    }
    else{
        fp=fopen(arg[1],"r");
        for(i=0;i<185;i++)
            s[i].read(fp);
        fclose(fp);
        fp=fopen(arg[0],"rb+");
        printf("%s %X\n",arg[0],fp);
        write(fp);
        fclose(fp);
        puts("data wrote.");
    }



    /*while(scanf("%s",cmd)==1)
    {
        if(cmd[0]=='r')
        {
            //scanf("%s",fname);
            fp=fopen("d:\\game\\ekd4\\sv04d.e4s","rb");
            if(!fp)
            {
                printf("Can't open file");
                continue;
            }
            fseek(fp,0,SEEK_END),size=ftell(fp);
            fseek(fp,0x1369,SEEK_SET);
            for(i=0;i<185;i++)
            {
                fread(s+i,sizeof(data),1,fp);
                fprintf(stdout,"%s\n",name[i]);
                s[i].print(stdout);
                scanf("%d",&tmp);
            }
            fclose(fp);
            cmd[0]='o';
        }
        if(cmd[0]=='o')
        {
            //scanf("%s",fname);
            fp=fopen("tmp.txt","w");
            for(i=0;i<185;i++)
            {
                fprintf(fp,"%s\n",name[i]);
                s[i].print(fp);
            }
            fclose(fp);
            //system("tmp.txt");
        }
        if(cmd[0]=='c')
        {
            fp=fopen("tmp.txt","r");
            for(i=0;i<185;i++)
                s[i].read(fp);
            fclose(fp);
        }
        if(cmd[0]=='s')
        {
            fp=fopen("d:\\game\\ekd4\\sv04d.e4s","rb");
            fseek(fp,0,SEEK_END),size=ftell(fp);
            fseek(fp,0,SEEK_SET);
            wp=fopen("d:\\game\\ekd4\\sv05d.e4s","wb");
            write(fp,wp);
            fclose(fp);
            fclose(wp);
        }
        if(cmd[0]=='e')
            edit();
    }*/
}
