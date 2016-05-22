#include<stdio.h>
int C=1,n,base[1001],*v=&base[500],min,max;
void tree(int lr){
    scanf("%d",&n);
    if(n==-1)return;
    min<?=lr;
    max>?=lr;
    v[lr]+=n;
    tree(lr-1);
    tree(lr+1);
}
main(){
while(scanf("%d",&n) && n!=-1){
    for(min=-500;min<=500;min++)v[min]=0;
    v[min=max=0]=n;
    tree(-1);
    tree(1);
    printf("Case %d:\n",C++);
    printf("%d",v[min]);
    while(min++<max)printf(" %d",v[min]);
    puts("\n");
}
}
