#include<stdio.h>
#include<string.h>
int n,l;
char se[81];
void show(){
int i;
    putchar(se[0]);
    for(i=1;se[i];i++){
        if(!(i%64))putchar('\n');
        else if(!(i%4))putchar(' ');
        putchar(se[i]);
    }
    printf("\n%d\n",i);
}
void go(int d){
    if(!n)return;
    int i,j;
    for(i=1;i<=d/2;i++)
        if(!strncmp(&se[d-i],&se[d-i-i],i))return;
    if(!--n){
        se[d]=0;
        show();
        return;
    }
    for(i=0;i<l && n;i++){
        se[d]=i+'A';
        go(d+1);
    }
    
}
main(){
while(scanf("%d %d",&n,&l) && n+++l)go(0);
}
