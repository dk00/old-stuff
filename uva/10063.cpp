#include<stdio.h>
char set[11],rs[11],tmp=1;
void kp(int p){
if(!set[p]){
    rs[p]=0;
    puts(rs);
    return;
}
int i;
for(i=p-1;i>=0;i--)rs[i+1]=rs[i];
rs[0]=set[p];kp(p+1);
for(i=0;i<p;i++){
    tmp=rs[i];rs[i]=rs[i+1];rs[i+1]=tmp;
    kp(p+1);
}
}
main(){
for(gets(set);tmp;tmp=(gets(set)!=NULL),tmp?puts(""):tmp=tmp)kp(0);
}
