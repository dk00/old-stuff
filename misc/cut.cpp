#include<cstdio>
char tmp[1048576];
int fsize(FILE *fp)
{
    int n,tmp=ftell(fp);
    fseek(fp,0,SEEK_END);
    n=ftell(fp);
    fseek(fp,tmp,SEEK_SET);
    return n;
}
main(int m,char **arg)
{
    int i,n;
    if(m<4)return 0;
    FILE *in=fopen(arg[1],"rb"),*out=fopen(arg[2],"wb");
    if(!in || !out)return 0;
    if(sscanf(arg[3],"%d",&n)!=1)return 0;
    n=fsize(in)-n;
    while((i=fread(&tmp,sizeof(tmp[0]),sizeof(tmp)/sizeof(tmp[0]),in)) && (n-=i)>0)
        fwrite(&tmp,sizeof(tmp[0]),i,out);
    fclose(in);
    fclose(out);
}
