#include<stdio.h>
int min(int a,int b)
{
    if(a<b)return a;
    return b;
}
char name[50][999],tmp[500000];
int len[500];
main(int xx,char **t)
{
    //if(xx==1)while(1);
    int i,j,k,n,m,key;
    FILE *fp=fopen(t[1],"rb");
    fread(&n,sizeof(n),1,fp);
    fread(&m,sizeof(n),1,fp);
    fread(&key,sizeof(n),1,fp);
    key>>=24;
    for(k=0;k<n;k++)
    {
        fread(name[k],sizeof(name[k][0]),124,fp);
        fread(len+k,sizeof(len[k]),1,fp);
    }
    for(k=0;k<n;k++)
    {
        i=len[k];
        FILE *out=fopen(name[k],"wb");
        while(i>0)
        {
            int p;
            for(p=0;p<m;p++)
                tmp[p]=0;
            j=fread(tmp,1,m,fp);
            for(p=0;p<j;p++)
                tmp[p]^=key;
            fwrite(tmp,1,min(i,m),out);
            i-=j;
        }
        fclose(out);
    }
    fclose(fp);
}