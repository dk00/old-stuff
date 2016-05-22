#include<stdio.h>
#include<string.h>
int n,wn,use[256],link[256][256];
char s[10000][21];
void show(){
int i,j;
    while(wn--){
        for(i=0;i<256;i++)
            if(use[i]==1)break;
        putchar(i);
        use[i]--;
        for(j=0;j<256;j++)
            if(link[i][j])
                use[j]--;
    }
    puts("");
}
void ordercmp(char *s1,char *s2){
    for(;s1[0]==s2[0] && s1[0] && s2[0];s1=&s1[1],s2=&s2[1]);
    if(s1[0] && s2[0] && !link[s1[0]][s2[0]]){
        use[s2[0]]++;
        link[s1[0]][s2[0]]=1;
    }
}
void newword(char *s){
    for(;s[0];s=&s[1]){
        if(!use[s[0]]){
            wn++;
            use[s[0]]=1;
        }
    }
}
main(){
int i,j;
for(n=0;gets(s[n]) && strcmp(s[n],"#");n++){
    newword(s[n]);
    if(n)
        ordercmp(s[n-1],s[n]);
}
show();
}
