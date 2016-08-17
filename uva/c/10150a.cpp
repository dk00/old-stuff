#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char word[26000][17],q[26000][17];
int n,l[26000],r[26000];
int _strcmp(const void *a,const void *b){
    return strcmp((char *)a,(char *)b);
}
int search(int stt,int end,char *key){
    if(stt>end)return 0;
    int mid=(stt+end)/2;
    if(!strcmp(key,word[mid])){
        if(r[mid]==1)return 0;
        r[mid]=1;
        return 1;
    }
    if(strcmp(key,word[mid])<0)return search(stt,mid-1,key);
    return search(mid+1,end,key);
}
void show(int p){
    if(p<0)return;
    show(l[p]);
    puts(q[p]);
}
main(){
char c,skip,now[100],s1[100],s2[100];
int i,j,k,find;
for(n=0;gets(word[n]) && *word[n];n++);
if(n>=26000)abort();
qsort(word,n,sizeof(word[0]),_strcmp);
while(scanf("%s %s",s1,s2)==2){
    if(strlen(s1)-strlen(s2)){
        puts("No solution.");
        continue;
    }
    for(i=0;i<26000;i++){
        l[i]=-1;
        r[i]=0;
    }
    if(!search(0,n-1,s1)){
        puts("No solution.");
        continue;
    }
    strcpy(q[0],s1);
    find=-1;
    for(i=0,j=1;i<j;i++){
        strcpy(now,q[i]);
        if(!strcmp(now,s2)){
            find=i;
            break;
        }
        for(k=0;(skip=now[k]);k++){
            for(c='a';c<='z';c++){
                if(c==skip)continue;
                now[k]=c;

                if(search(0,n-1,now)){
                    strcpy(q[j],now);
                    l[j++]=i;
                }
            }
            now[k]=skip;
        }
    }
    if(find>=0){
        show(find);
    }
    else puts("No solution.");
}
}
