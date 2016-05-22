#include<stdio.h>
const char o0[4][7]={"%02X","%02x","%03o","%03u"};
char *in,*out,spc[100]="% 1s";
n=8;
main(int m,char **a)
{
    out=o0[1];
    int i,j,k;
    for(i=1;i<m;i++)
    {
        if(!strcmp(a[i],"-c"))
            sscanf(a[++i],"%d",&n);
        else if(!strcmp(a[i],"-s"))
        {
            sscanf(a[++i],"%d",&j);
            sprintf(spc,"%% %ds",j);
        }
        else if(!strcmp(a[i],"-X"))out=o0[0];
        else if(!strcmp(a[i],"-x"))out=o0[1];
        else if(!strcmp(a[i],"-o"))out=o0[2];
        else if(!strcmp(a[i],"-u"))out=o0[3];
        else in=a[i];
    }
    FILE *fp=fopen(in,"rb");
    unsigned char *tmp=malloc(n);
    i=0;
    while((j=fread(tmp,1,n,fp)))
    {
        printf("%06x:",i);
        i+=j;
        printf(out,tmp[0]);
        for(k=1;k<j;k++)
        {
            printf(spc,"");
            printf(out,tmp[k]);
        }
        puts("");
    }
}

