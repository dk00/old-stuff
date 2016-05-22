/*
ID: s0000151
PROG: transform
LANG: C++
*/

#include<stdio.h>
#include<string.h>
#define DEBUG 0
char before[10][11],to[10][11],after[10][11];
int i,j,n;
int cmp(){
    for(i=0;i<n;i++)if(strcmp(to[i],after[i]))return 0;
    return 1;
}
int tran1(){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            to[j][n-i-1]=before[i][j];
    return cmp();
}
int tran2(){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            to[n-i-1][n-j-1]=before[i][j];
    return cmp();
}
int tran3(){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            to[n-j-1][i]=before[i][j];
    return cmp();
}
int tran4(){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            to[i][n-j-1]=before[i][j];
    if(cmp())return 1;
    for(i=0;i<n;i++)strcpy(before[i],to[i]);
    return 0;
}
int tran6(){
    for(i=0;i<n;i++)strcpy(to[i],before[i]);
    return cmp();
}
main(){
if(!DEBUG){freopen("transform.in","r",stdin);
freopen("transform.out","w",stdout);}
scanf("%d%c",&n,&before[0][0]);
for(i=0;i<n;i++)scanf("%s",before[i]);
for(i=0;i<n;i++)scanf("%s",after[i]);
if(tran1())puts("1");
else if(tran2())puts("2");
else if(tran3())puts("3");
else if(tran4())puts("4");
else if(tran6())puts("6");
else if(tran1() || tran2() || tran3())puts("5");
else puts("7");
if(DEBUG)scanf(" ");
}
