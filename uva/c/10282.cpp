#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct word{
    char eng[11],fore[11];
};
int cmp(const void *a,const void *b){
    return strcmp(((word *)a)->fore,((word *)b)->fore);
}
word word1[100000];
char *search(int s,int e,char *s1){
    if(s>e)return NULL;
    int m=(s+e)/2;
    if(!strcmp(word1[m].fore,s1))return word1[m].eng;
    else if(strcmp(word1[m].fore,s1)>0)return search(s,m-1,s1);
    else return search(m+1,e,s1);
}
main(){
char s[10000],s1[11],*s2;
int n;
for(n=0;gets(s) && s[0];n++)
    sscanf(s,"%s %s",word1[n].eng,word1[n].fore);
qsort(word1,n,sizeof(word1[0]),cmp);
while(scanf("%s",s1)!=EOF){
    s2=search(0,n-1,s1);
    if(s2==NULL)puts("eh");
    else puts(s2);
}
}
