#include<stdio.h>
int linenumget(int s[]){
int n,c;
    c=getchar();
    for(n=0;c!='\n';n++){
        while((c<'0' || c>'9') && c!='\n')c=getchar();
        if(c=='\n')break;
        ungetc(c,stdin);
        scanf("%d%c",&s[n],&c);
    }
    return n;
}
main(){
int i,n,s[10000];
while(n=linenumget(s)){
    printf("%d numbers:",n);
    for(i=0;i<n;i++)printf(" %d",s[i]);
    puts("");
}
}
