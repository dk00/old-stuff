#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char word[200][17],q[200][17];
int n,l[200],r[200];
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
char c,skip,now[100],s1[100],s2[100],line[1000];
int i,j,k,t,find;
scanf("%d%c",&t,&c);
gets(line);
while(t--){
    for(n=0;gets(word[n]) && strcmp(word[n],"*");n++);
    qsort(word,n,sizeof(word[0]),_strcmp);
    while(1){
        if(gets(line)==NULL)return 0;
        if(!(*line))break;
        sscanf(line,"%s %s",s1,s2);
        for(i=0;i<200;i++){
            l[i]=-1;
            r[i]=0;
        }
        strcpy(q[0],s1);
        find=-1;
        l[0]=0;
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
                        l[j++]=l[i]+1;
                    }
                }
                now[k]=skip;
            }
        }
        printf("%s %s %d\n",s1,s2,l[find]);
    }
    if(t)puts("");
}
}
