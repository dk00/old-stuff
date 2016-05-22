#include<stdio.h>
#include<string.h>
char graph[2000][70];
main(){
int i,j,h,t,min,max,C=1;
char path[70];
scanf("%d",&t);
while(t--){
    scanf("%s",path);
    for(h=0;h<2000;h++)
        for(i=0;i<60;i++)graph[h][i]=' ';
    max=0;h=1000;min=2000;
    for(i=0;path[i];i++){
        if(path[i]=='R'){
            graph[h][i]='/';
            h++;
        }
        else if(path[i]=='F'){
            h--;
            graph[h][i]='\\';
        }
        else graph[h][i]='_';
        max>?=h;
        min<?=h;
    }
    printf("Case #%d:\n",C++);
    for(i=max+100;i>=min-100;i--){
        for(j=55;j>=0 && graph[i][j]==' ';j--)graph[i][j]=0;
        if(j<0)continue;
        printf("| ");
        puts(graph[i]);
    }
    printf("+-");
    for(i=strlen(path)+1;i--;)putchar('-');
    puts("\n");
}
}
