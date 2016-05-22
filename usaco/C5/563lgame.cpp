/*
ID: s0000151
PROG: lgame
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,max=0,pt[256],score[40000];
char word[40000][8];
int charcmp(const void *a,const void *b){
    return *(char *)a-*(char *)b;
}
int wordcmp(const void *a,const void *b){
    return strcmp((char *)a,(char *)b);
}
int search(int stt,int end,char *key){
    if(stt>end)return 0;
    int mid=(stt+mid)/2;
    if(!strcmp(word[mid],key))return score[mid];
    else if(strcmp(key,word[mid])<0)return search(stt,mid-1);
    return search(mid+1,end);
}
void cut(char *key,int scr){
    max>?=scr+search(0,n-1,key);;
    char tmp[8];
    int i,p,l=strlen(key);
    for(i=1;i<l;i++){
        p=search(0,n-1,strncpy(tmp,key,i));
        if(p){
        }
    }
}
main(){
int i,j;
char key[8];
pt['q']=7,pt['w']=6,pt['e']=1,pt['r']=2,pt['t']=2,pt['y']=5,pt['u']=4;
pt['i']=1,pt['o']=3,pt['p']=5,pt['a']=2,pt['s']=1,pt['d']=4,pt['f']=6;
pt['g']=5,pt['h']=5,pt['j']=7,pt['k']=6,pt['l']=3,pt['z']=7,pt['x']=7;
pt['c']=4,pt['v']=6,pt['b']=5,pt['n']=2,pt['m']=5;
freopen("lgame.dict","r",stdin);
for(n=0;scanf("%s",word[n]) && word[n][0]-'.';n++)
    qsort(word[i],strlen(word[i]),sizeof(word[i][0]),charcmp);
qsort(word,n,sizeof(word[0]),wordcmp);
for(i=0;i<n;i++)
    for(j=0;word[i][j];j++)
        score[i]+=pt[word[i][j]];
freopen("lgame.in","r",stdin);
freopen("lgame.out","w",stdout);
scanf("%s",key);
qsort(key,strlen(key),sizeof(key[0]),charcmp);
max>?=search(0,n-1,key);
cut(key,0);
show(key,0);
}
