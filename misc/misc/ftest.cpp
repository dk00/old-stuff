#include<cstdio>
#include<cstring>
unsigned char buff[1024*1024];
int fsize(FILE *fp)
{
    int a,b;
    a=ftell(fp);
    fseek(fp,0,SEEK_END);
    b=ftell(fp);
    fseek(fp,a,SEEK_SET);
    return b;
}
unsigned char s[]={0x11,0x06,0x18,0xec,0x86,0x6d,0x8b,0x32,0x3b},
              t[]={0x0f,0x04,0x2d,0x43,0x1c,0xeb,0xe2,0x36,0x3a};
int main()
{
    
    int i,j,n,type;
    char tmp[1000];
    unsigned char tmp1[10];
    printf("Input file name (1.ima_0000.exe 2.EXA_0000.EXE): ");
    gets(tmp);
    if(sscanf(tmp,"%d",&type)!=1 ||(type!=1 && type!=2))
        return 0;
    if(type==1)
        strcpy(tmp,"ima_0000.exe");
    else
        strcpy(tmp,"EXA_0000.EXE");
    FILE *f1=fopen(tmp,"rb");
    if(!f1)
    {
        puts("Can't open the file");
        return 0;
    }
    n=fsize(f1);
    printf("%s Size: %d\n",tmp,n);
    fread(buff,1,n,f1);
    fclose(f1);
    if(type==1)
    {
        printf("2C3FH:");
        for(i=0;i<9;i++)
            printf(" %02X",tmp1[i]=buff[0x2c3f+i]);
        puts("");
        for(i=0;i<9;i++)
            if(tmp1[i]!=t[i])break;
        if(i>=9)
        {
            puts("The file is already updated.");
            return 0;
        }
        for(i=0;i<9;i++)
            buff[0x2c3f+i]=t[i];
    }
    else
    {
        printf("2B13H:");
        for(i=0;i<9;i++)
            printf(" %02X",tmp1[i]=buff[0x2b13+i]);
        puts("");
        for(i=0;i<9;i++)
            if(tmp1[i]!=s[i])break;
        if(i>=9)
        {
            puts("The file is already updated.");
            return 0;
        }
        for(i=0;i<9;i++)
            buff[0x2b13+i]=s[i];
    }
    f1=fopen(tmp,"wb");
    fwrite(buff,1,n,f1);
}
