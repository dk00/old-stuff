#include<stdio.h>
#include<string.h>
#define write(x) fwrite(&(x),sizeof(x),1,stdout);
unsigned fsize(char *file)
{
    FILE *fp=fopen(file,"r");
    if(!fp)return -1;
    fseek(fp,0,SEEK_END);
    int tmp=ftell(fp);
    fclose(fp);
    return tmp;
}
char tmp[4097];
char arc[1000]="file.arc",file[30][124];
main(int m,char **t)
{
    unsigned i,j,k,n=0,size=512;
    unsigned char key=0xff;
    for(i=1;i<m;i++){
        if(strcmp(t[i],"-b")==0)
        {
            if(sscanf(t[++i],"%u",&j)==1)
                size=j;
        }
        else if(strcmp(t[i],"-xor")==0)
        {
            if(sscanf(t[++i],"%x",&j)==1)
                key=j;
        }
        else if(strcmp(t[i],"-dest")==0)
            strcpy(arc,t[++i]);
        else
        {
            memset(file[n],0,sizeof(file[n]));
            if(fsize(t[i])>=0 && strlen(t[i])<128)
                strcpy(file[n++],t[i]);
            else
                printf("File not found - %s\n",t[i]);
        }
    }
    freopen(arc,"wb",stdout);
    write(n);
    write(size);
    for(i=0;i<4;i++)
        write(key);
    for(i=0;i<n;i++)
    {
        write(file[i]);
        j=fsize(file[i]);
        write(j);
    }
    for(i=0;i<n;i++)
    {
        freopen(file[i],"rb",stdin);
        while(1)
        {
            memset(tmp,0,size);
            j=fread(tmp,1,size,stdin);
            for(k=0;k<j;k++)
                tmp[k]^=key;
            if(j)fwrite(tmp,1,size,stdout);
            if(j<size)break;
        }
        fclose(stdin);
    }
    fclose(stdout);
}
