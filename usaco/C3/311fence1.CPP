/*
ID: s0000151
PROG: fence
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
#define MAX 1025
int v[MAX],link[MAX][MAX],c[MAX],p=0,i;
void go(int s){
    while(v[s]){
        for(i=1;i<MAX && !link[i][s];i++);
        v[s]--;v[i]--;
        link[i][s]--;link[s][i]--;
        go(i);
    }
    c[p++]=s;
}
main(){
if(!DEBUG){freopen("fence.in","r",stdin);
freopen("fence.out","w",stdout);}
int s,f,l1,l2;
for(s=0;s<MAX;s++){
    v[s]=link[s][s]=0;
    for(f=0;f<s;f++)link[s][f]=link[f][s]=0;
}
for(scanf("%d",&f);f--;){
    scanf("%d %d",&l1,&l2);
    v[l1]++;v[l2]++;
    link[l1][l2]++;link[l2][l1]++;
}
for(s=1;s<MAX && v[s]%2!=1;s++);
if(s>=MAX)for(s=1;v[s]==0;s++);
go(s);
while(p--)printf("%d\n",c[p]);
if(DEBUG)scanf(" ");
}
