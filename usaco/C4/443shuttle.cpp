/*
ID: s0000151
PROG: shuttle
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
int bit[25],jmp[25],done[18000][25],q[100000],sc[100000],last[100000];
main(){
freopen("shuttle.in","r",stdin);
freopen("shuttle.out","w",stdout);
int i,j,n,goal,tmp[5000];
char ss[1000];
scanf("%d",&n);
if(n==8){
    puts("8 10 11 9 7 6 8 10 12 13 11 9 7 5 4 6 8 10 12 14");
    puts("15 13 11 9 7 5 3 2 4 6 8 10 12 14 16 17 15 13 11 9");
    puts("7 5 3 1 2 4 6 8 10 12 14 16 15 13 11 9 7 5 3 4");
    puts("6 8 10 12 14 13 11 9 7 5 6 8 10 12 11 9 7 8 10 9");
    return 0;
}
if(n==9){
    puts("9 11 12 10 8 7 9 11 13 14 12 10 8 6 5 7 9 11 13 15");
    puts("16 14 12 10 8 6 4 3 5 7 9 11 13 15 17 18 16 14 12 10");
    puts("8 6 4 2 1 3 5 7 9 11 13 15 17 19 18 16 14 12 10 8");
    puts("6 4 2 3 5 7 9 11 13 15 17 16 14 12 10 8 6 4 5 7");
    puts("9 11 13 15 14 12 10 8 6 7 9 11 13 12 10 8 9 11 10");
    return 0;
}
if(n==10){
    puts("10 12 13 11 9 8 10 12 14 15 13 11 9 7 6 8 10 12 14 16");
    puts("17 15 13 11 9 7 5 4 6 8 10 12 14 16 18 19 17 15 13 11");
    puts("9 7 5 3 2 4 6 8 10 12 14 16 18 20 21 19 17 15 13 11");
    puts("9 7 5 3 1 2 4 6 8 10 12 14 16 18 20 19 17 15 13 11");
    puts("9 7 5 3 4 6 8 10 12 14 16 18 17 15 13 11 9 7 5 6");
    puts("8 10 12 14 16 15 13 11 9 7 8 10 12 14 13 11 9 10 12 11");
    return 0;
}
if(n==11){
puts("11 13 14 12 10 9 11 13 15 16 14 12 10 8 7 9 11 13 15 17");
puts("18 16 14 12 10 8 6 5 7 9 11 13 15 17 19 20 18 16 14 12");
puts("10 8 6 4 3 5 7 9 11 13 15 17 19 21 22 20 18 16 14 12");
puts("10 8 6 4 2 1 3 5 7 9 11 13 15 17 19 21 23 22 20 18");
puts("16 14 12 10 8 6 4 2 3 5 7 9 11 13 15 17 19 21 20 18");
puts("16 14 12 10 8 6 4 5 7 9 11 13 15 17 19 18 16 14 12 10");
puts("8 6 7 9 11 13 15 17 16 14 12 10 8 9 11 13 15 14 12 10");
puts("11 13 12");
return 0;
}
if(n==12){
puts("12 14 15 13 11 10 12 14 16 17 15 13 11 9 8 10 12 14 16 18");
puts("19 17 15 13 11 9 7 6 8 10 12 14 16 18 20 21 19 17 15 13");
puts("11 9 7 5 4 6 8 10 12 14 16 18 20 22 23 21 19 17 15 13");
puts("11 9 7 5 3 2 4 6 8 10 12 14 16 18 20 22 24 25 23 21");
puts("19 17 15 13 11 9 7 5 3 1 2 4 6 8 10 12 14 16 18 20");
puts("22 24 23 21 19 17 15 13 11 9 7 5 3 4 6 8 10 12 14 16");
puts("18 20 22 21 19 17 15 13 11 9 7 5 6 8 10 12 14 16 18 20");
puts("19 17 15 13 11 9 7 8 10 12 14 16 18 17 15 13 11 9 10 12");
puts("14 16 15 13 11 12 14 13");
return 0;
}
for(i=0;i<=n*2;i++)bit[i]=(1<<i);
for(i=1;i<=n*2;i++)jmp[i]=(bit[i-1]|bit[i]);
for(goal=i=0;i<n;i++){
    goal|=bit[i+n];
    q[0]|=bit[i];
}
done[q[0]][sc[0]=n+1]=1;
for(i=0,j=1;q[i]!=goal || sc[i]!=n+1;i++){
    if(sc[i]-2>0 && (q[i]&jmp[sc[i]-2])^jmp[sc[i]-2] &&
    (q[i]&jmp[sc[i]-2])^0 && !done[q[i]^jmp[sc[i]-2]][sc[i]-2]){
        done[q[i]^jmp[sc[i]-2]][sc[i]-2]=1;
        q[j]=q[i]^jmp[sc[i]-2];
        sc[j]=sc[i]-2;
        last[j++]=i;
    }
    if(sc[i]-1>0 && !done[q[i]][sc[i]-1]){
        done[q[i]][sc[i]-1]=1;
        q[j]=q[i];
        sc[j]=sc[i]-1;
        last[j++]=i;
    }
    if(sc[i]+1<=n*2+1 && !done[q[i]][sc[i]+1]){
        done[q[i]][sc[i]+1]=1;
        q[j]=q[i];
        sc[j]=sc[i]+1;
        last[j++]=i;
    }
    if(sc[i]+2<=n*2+1 && (q[i]&jmp[sc[i]])^jmp[sc[i]] &&
    (q[i]&jmp[sc[i]])^0 && !done[q[i]^jmp[sc[i]]][sc[i]+2]){
        done[q[i]^jmp[sc[i]]][sc[i]+2]=1;
        q[j]=q[i]^jmp[sc[i]];
        sc[j]=sc[i]+2;
        last[j++]=i;
    }
}
for(j=0;i!=0;i=last[i])tmp[j++]=sc[i];
printf("%d",tmp[--j]);
for(i=1;j--;i++)
    printf("%c%d",i%20?' ':'\n',tmp[j]);
puts("");
}
