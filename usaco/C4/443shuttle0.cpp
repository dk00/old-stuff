/*
ID: s0000151
PROG: shuttle
LANG: C++
*/
#include<stdio.h>
main(){
freopen("shuttle.in","r",stdin);
freopen("shuttle.out","w",stdout);
int i,j,n,p=0,sp,path[1000];
scanf("%d",&n);
for(sp=n+1,i=1;i<=n;i++){
    for(j=2;j<=i;j++){
        if(i%2)path[p++]=(sp-=2);
        else path[p++]=(sp+=2);
    }
    if(i%2)path[p++]=--sp;
    else path[p++]=++sp;
}
for(i=1;i<=n;i++){
    if(n%2)path[p++]=(sp+=2);
    else path[p++]=(sp-=2);
}
for(i=n;i>=1;i--){
    if(i%2)path[p++]=--sp;
    else path[p++]=++sp;
    for(j=2;j<=i;j++){
        if(i%2)path[p++]=(sp-=2);
        else path[p++]=(sp+=2);
    }
}
printf("%d",path[0]);
for(i=1;i<p;i++)printf("%c%d",i%20?' ':'\n',path[i]);
puts("");
}
