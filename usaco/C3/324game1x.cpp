/*
ID: s0000151
PROG: game1
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
main(){
if(!DEBUG){freopen("game1.in","r",stdin);
freopen("game1.out","w",stdout);}
int n,odd=0,even=0,l=0,r=0,p[2]={0,0},b[101],k=1;
scanf("%d",&n);
for(r=0;r<n;r++){
    scanf("%d",&b[r]);
    if(r%1)even+=b[r];
    else odd+=b[r];
}r--;
if(n%2)p[k=!k]=b[b[l]>b[r]?l++:r--];
while(n-=2){
    if(l%2){    //l even,r odd
        if(even>=odd)even-=(p[k=!k]+=b[l++]);
        else odd-=(p[k=!k]+=b[r--]);
    }
    else{       //l odd,r even
        if(even>=odd)even-=(p[k=!k]+=b[r--]);
        else odd-=(p[k=!k]+=b[l++]);
    }
    if(l%2)even-=(p[k=!k]+=b[b[l]>b[r]?l++:r--]);
    else odd-=(p[k=!k]+=b[b[l]>b[r]?l++:r--]);
}
printf("%d %d\n",p[0],p[1]);
if(DEBUG)scanf(" ");
}
