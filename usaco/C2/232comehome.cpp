/*
ID: s0000151
PROG: comehome
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
main(){
if(!DEBUG){freopen("comehome.in","r",stdin);
freopen("comehome.out","w",stdout);}
int n,p,i,j,dis[100],link[100][100],pt[256],start,re[100],min,r;
char l1,l2,c,ch[100];
for(i='A';i<='Z';i++)pt[i]=-1;
for(i='a';i<='z';i++)pt[i]=-1;
for(i=0;i<100;i++){
    for(j=0;j<100;j++)link[i][j]=30000;
}
scanf("%d%c",&p,&c);r=p;
for(n=0;p--;){
    scanf("%c %c %d%c",&l1,&l2,&i,&c);
    if(pt[l1]<0){
        pt[l1]=n;
        ch[n++]=l1;
    }
    if(pt[l2]<0){
        pt[l2]=n;
        ch[n++]=l2;
    }
    link[pt[l1]][pt[l2]]=i;
    link[pt[l2]][pt[l1]]=i;
}
for(i=0;i<n;i++){
    dis[i]=link[pt['Z']][i];
    re[i]=0;
}
re[pt['Z']]=1;
while(1){
    for(i=0;re[i] && i<n;i++);
    for(min=i++;i<n;i++){
        if(!re[i] && dis[i]<dis[min])min=i;
    }
    if(ch[min]>='A' && ch[min]<='Z')break;
    re[min]=1;
    for(i=0;i<n;i++){
        if(!re[i] && link[min][i]<=1000)
            dis[i]<?=dis[min]+link[min][i];
    }
}
printf("%c %d\n",ch[min],dis[min]);
if(DEBUG)scanf(" ");
}
