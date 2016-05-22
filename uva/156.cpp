#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char word[1200][21];
struct pair{
    char s1[21],s2[21];
    int mark;
}ww[1200];
int numcmp(const void *a,const void *b){
    return *(char *)a-*(char *)b;
}
int wordcmp(const void *a,const void *b){
    return strcmp(((pair *)a)->s2,((pair *)b)->s2);
}
int wordcmp2(const void *a,const void *b){
    return strcmp(((pair *)a)->s1,((pair *)b)->s1);
}
main(){
int i,j,n;
for(n=0;scanf("%s",word[n]) && strcmp(word[n],"#");n++){
    strcpy(ww[n].s1,word[n]);
    for(i=0;word[n][i];i++)word[n][i]=tolower(word[n][i]);
    qsort(word[n],strlen(word[n]),sizeof(word[0][0]),numcmp);
    strcpy(ww[n].s2,word[n]);
}
qsort(ww,n,sizeof(ww[0]),wordcmp);
for(i=0;i<n;i=j){
    for(j=i;!strcmp(ww[i].s2,ww[j].s2);j++);
    if(i+1==j)ww[i].mark=1;
}
qsort(ww,n,sizeof(ww[0]),wordcmp2);
for(i=0;i<n;i++)
    if(ww[i].mark)puts(ww[i].s1);
}
