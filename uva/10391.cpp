#include<stdio.h>
#include<string.h>
char word[120000][100];
int search(int stt,int end,char *key){
    if(stt>end)return 0;
    int mid=(stt+end)/2;
    if(!strcmp(word[mid],key))return 1;
    else if(strcmp(key,word[mid])<0)return search(stt,mid-1,key);
    return search(mid+1,end,key);
}
main(){
int i,j,n,len;
char s1[100],s2[100];
for(n=0;gets(word[n])!=NULL;n++);
for(i=0;i<n;i++){
    len=strlen(word[i]);
    for(j=1;j<len;j++){
        strncpy(s1,word[i],j);
        strcpy(s2,word[i]+j);
        s1[j]=0;
        if(search(0,n-1,s1) && search(0,n-1,s2)){
            puts(word[i]);
            break;
        }
    }
}
}
