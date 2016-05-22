#include<stdio.h>
int link[26][26],linked[26],n;
void go(int node){
    int i;
    for(i=0;i<n;i++){
        if(i==node) continue;
        if(!linked[i] && link[node][i]){
            linked[i]=1;go(i);
        }
    }
}
main(){
int first=1,i,num,l1,l2;
char c;
while(1){
    scanf("%c%c",&c);
    n=c-'A'+1;num=0;
    for(l1=0;l1<n;l1++){
	   linked[l1]=0;
	   for(l2=0;l2<n;l2++)
		  link[l1][l2]=0;
    }
    while(1){
	   scanf("%c",&c);if(c=='\n') break;
	   l1=c-'A';
       if(scanf("%c",&c)==EOF){
           l2=c-'A';
	       link[l1][l2]=1;link[l2][l1]=1;
	       break;
        }
       l2=c-'A';
	   link[l1][l2]=1;link[l2][l1]=1;
	   scanf("%c");
    }
    for(i=0;i<n;i++){
	   if(!linked[i]){
		  linked[i]=1;go(i);num++;
	   }
    }
    if(!first)
        printf("\n\n");
    else first=0;
    printf("%d",num);
}
}
