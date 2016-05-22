/*
ID: s0000151
PROG: lamps
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
int j,on[101],off[101],n,lamp[102],f=0;
void check(){
    for(j=1;j<=n;j++){
        if(on[j] && !lamp[j])return;
        if(off[j] && lamp[j])return;
    }
    for(j=1;j<=n;j++)printf("%d",lamp[j]);
    puts("");
    f++;
}
void button1(){
    for(j=1;j<=n;j++)lamp[j]=!lamp[j];
}
void button2(){
    for(j=1;j<=n;j+=2)lamp[j]=!lamp[j];
}
void button3(){
    for(j=2;j<=n;j+=2)lamp[j]=!lamp[j];
}
void button4(){
    for(j=1;j<=n;j+=3)lamp[j]=!lamp[j];
}
main(){
if(!DEBUG){freopen("lamps.in","r",stdin);
freopen("lamps.out","w",stdout);}
int c,i;
scanf("%d %d",&n,&c);
for(i=0;i<=n;i++)on[i]=off[i]=0;
for(scanf("%d",&i);i>0;scanf("%d",&i))on[i]=1;
for(scanf("%d",&i);i>0;scanf("%d",&i))off[i]=1;
for(i=1;i<=n+1;i++)lamp[i]=1;
if(c<=0){check();if(!f)puts("IMPOSSIBLE");return 0;}
button1();
check();
button1();
if(c>1){
    button3();button4();
    check();
    button3();button4();
}
button2();
check();
button2();
button4();
check();
button4();
if(c>1){
    button1();button4();
    check();
    button1();button4();
}
button3();
check();
button3();
if(c>1){
    button2();button4();
    check();
    button2();button4();
}
check();
if(!f)puts("IMPOSSIBLE");
if(DEBUG)scanf(" ");
}
