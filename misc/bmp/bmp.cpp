#include<stdio.h>
#include"window.h"
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
inline COLORREF getColor(const unsigned char *buf,int bit,int i)
{
    int p=(i+1)*bit;
    unsigned z,n=bit;
    if(p%8>0){
        z=buf[p/8+1]&((1<<(p%8))-1);
        n-=p%8;
    }
    p=(p-1)/8;
    while(n>=8){
        z=(z<<8)|buf[p--];
        n-=8;
    }
    if(bit>0)
        z=(z<<n)|(buf[p]>>(8-n));
    return RGB(z>>(bit-bit/3),(z>>(bit/3))&((1<<(bit/3))-1),z&((1<<(bit/3))-1));
}
bool load(Window& W)
{
    printf("%d\n",sizeof(head));
    FILE *fp=fopen("e:\\pic\\Desktop\\sora.bmp","rb");
    if(!fp)return false;
    head h;
    info inf;
    fseek(fp,2,SEEK_CUR);
    fread(&h,sizeof(h),1,fp);
    fread(&inf,sizeof(inf),1,fp);
    fseek(fp,h.offset,SEEK_SET);

    PAINTSTRUCT ps;
    HDC hdc=BeginPaint(W.hwnd,&ps);
    int i,j,buflen=((inf.w*inf.bit+7)/8+3)/4*4;
    unsigned char buf[5760];
    for(i=inf.h-1;i>=0;i--){
        fread(buf,1,buflen,fp);
        for(j=0;j<inf.w;j++)
            if(i<W.h && j<W.w)
                SetPixel(hdc,j,i,getColor(buf,24,j));
    }
    
    EndPaint(W.hwnd,&ps);

    fclose(fp);
    return true;
}
