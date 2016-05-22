#include<stdio.h>
int n;
char path[9]="abcdefgh",c,spc[9][17]={"","  ","    ","      ","        "
,"          ","            ","              ","                ",};
void dfs(int d){
    if(d>=n){
        printf("%swriteln(%c",spc[d],path[0]);
        for(d=1;d<n;d++)printf(",%c",path[d]);
        puts(")");
        return;
    }
    printf("%sif %c < %c then\n",spc[d],path[d-1],path[d]);
    dfs(d+1);
    int i;
    for(i=d;i>1;i--){
        c=path[i];path[i]=path[i-1];path[i-1]=c;
        printf("%selse if %c < %c then\n",spc[d],path[i-2],path[i-1]);
        dfs(d+1);
    }
    printf("%selse\n",spc[d]);
    c=path[0];path[0]=path[1];path[1]=c;
    dfs(d+1);
    for(i=0;i<d;i++){
        c=path[i];path[i]=path[i+1];path[i+1]=c;
    }
}
main(){
int i,t;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    puts("program sort(input,output);\nvar");
    printf("%c",path[0]='a');
    for(i=1;i<n;i++) printf(",%c",path[i]='a'+i);
    puts(" : integer;\nbegin");
    printf("  readln(a");
    for(i=1;i<n;i++)printf(",%c",path[i]);
    puts(");");
    dfs(1);
    puts("end.");
    if(t)puts("");
}
}
