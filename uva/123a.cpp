#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct KWIC{
    char tle[10001],key[1001];
    int id;
}kwic[2000];
int kwiccmp(const void *a,const void *b){
    int r=strcmp(((KWIC *)a)->key,((KWIC *)b)->key);
    return r?r:((KWIC *)a)->id-((KWIC *)b)->id;
}
void strlwr1(char *s){
    for(;s[0];s=&s[1])
        if(s[0]>='A' && s[0]<='Z')
            s[0]+=32;
}
void strupr1(char *s){
    for(;s[0];s=&s[1])
        if(s[0]>='a' && s[0]<='z')
            s[0]-=32;
}
char c,tmp[10001],ig[51][11],title[200][10001];
main(){
int i,j,k,l,y,gn,kn,tn;
for(gn=0;scanf("%s",ig[gn]) && strcmp(ig[gn],"::");gn++);
gets(tmp);
for(tn=0;gets(title[tn])!=NULL;tn++)strlwr1(title[tn]);
for(kn=i=0;i<tn;i++){
    for(j=0;title[i][j];j=k){
        strcpy(tmp,title[i]);
        while(tmp[j]&&(tmp[j]<'A'||(tmp[j]>'Z' &&tmp[j]<'a')||tmp[j]>'z'))j++;
        for(k=j;tmp[k]&&((tmp[k]>='A'&&tmp[k]>'Z')||(tmp[k]<'a'&&tmp[k]>'z'));k++);
        c=tmp[k];
        tmp[k]=0;
        for(y=1,l=0;l<gn;l++)
            if(!strcmp(&tmp[j],ig[l]))y=0;
        if(!y)continue;
        strupr1(&tmp[j]);
        kwic[kn].id=kn;
        strcpy(kwic[kn].key,&tmp[j]);
        tmp[k]=c;
        strcpy(kwic[kn++].tle,tmp);
    }
}
qsort(kwic,kn,sizeof(kwic[0]),kwiccmp);
for(i=0;i<kn;i++)puts(kwic[i].tle);
}
