#include<stdio.h>
#include<malloc.h>
int *s[92],len[92],*tmp;
main(){
int n,i,j,x,y,z;
for(i=0;i<91;i++)s[i]=(int *)malloc(sizeof(int)*3);
while(scanf("%d",&n)){
    if(!n)break;
    for(i=0;i<n*3;i+=3){
        scanf("%d %d %d",&x,&y,&z);
    }
}
}
