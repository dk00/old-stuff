#include<stdio.h>
struct head
{
    int size,dummy,offset;
};
struct info
{
    int len,w,h;
    short plane,bit;
    int c,size,hres,vres,color,icolor;
};
inline int getColor(const unsigned char *buf,int bit,int i)
{
    int p=(i+1)*bit;
    unsigned z=0,n=bit;
    if(p%8>0){
        z=buf[p/8+1]&((1<<(p%8))-1);
        n-=p%8;
    }
    printf("%X ",z);
    p=(p-1)/8;
    while(n>=8){
        z=(z<<8)|buf[p--];
        n-=8;
    }
    printf("%X ",z);
    if(n>0)
        z=(z<<n)|(buf[p]>>(8-n));
    printf("%X ",z);
    printf("%X %X %X\n",z>>(bit-bit/3),(z>>(bit/3))&((1<<(bit/3))-1),((1<<(bit/3))-1)&z);
    //return RGB(0,g,b);
}
bool load()
{
    printf("%d\n",sizeof(head));
    FILE *fp=fopen("e:\\pic\\Desktop\\sora.bmp","rb");
    if(!fp)return false;
    head h;
    info inf;
    fseek(fp,2,SEEK_CUR);
    fread(&h,sizeof(h),1,fp);
    printf("Size: %d\n",h.size);
    printf("Offset: %d\n",h.offset);
    fread(&inf,sizeof(inf),1,fp);
    printf("Header len: %d\n",inf.len);
    printf("%d x %d %d-bis\n",inf.w,inf.h,inf.bit);
    printf("Compress: %d\n",inf.c);
    printf("size: %d\n",inf.c);
    printf("color: %d\n",inf.color);
    
    fseek(fp,h.offset,SEEK_SET);
    unsigned char buf[99];
    fread(buf,1,10,fp);
    getColor(buf,24,0);
    
    fclose(fp);
    return true;
}
main()
{
    load();
}
