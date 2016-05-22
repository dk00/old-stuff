#include<stdio.h>
unsigned long use[12],vse[12],zero=0;
int n;
int dfs(unsigned long p,int d){
    if(d>=n){       //bingo!
        printf("Toppings: ");
        for(d=0;d<16;d++)
            if(p&(1<<d))printf("%c",'A'+d);
        puts("");
        return 1;
    }
    if(p&use[d] || (~p)&vse[d])return dfs(p,d+1);
    for(int i=0;i<16;i++){
        if((p|(1<<i))&use[d] || (~(p|(1<<i)))&vse[d]){
            if(dfs(p|(1<<i),d+1))return 1;
        }
    }
    return 0;
}
main(){
int i;
char s[1000];
while(gets(s)!=NULL){
    for(n=0;s[0]!='.';n++){
        use[n]=vse[n]=0;
        for(i=0;s[i]!=';' && s[i+1]!='\0';i+=2){
            if(s[i]=='+')use[n]|=(1<<(s[i+1]-'A'));
            else vse[n]|=(1<<(s[i+1]-'A'));
        }
        gets(s);
    }
    if(dfs(zero,0)==0)puts("No pizza can satisfy these requests.");
}
}
