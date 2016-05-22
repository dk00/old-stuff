/*
ID: s0000151
PROG: beads
LANG: C++
*/

#include<stdio.h>
#define Max(a,b) (a)>(b)?(a):(b)
#define Max4(a,b,c,d) Max(Max(a,b),Max(c,d))
main(){
freopen("beads.in","r",stdin);
freopen("beads.out","w",stdout);
char s[351],last,s1[351],s2[351];
int i,n,max,k,l,t=1;
scanf("%d%c",&n,&s[0]);
for(i=0;i<n;i++)scanf("%c",&s[i]);
for(max=i=k=l=0;i<n || t;k=0){
    if(s[i]=='w')
        for(;s[i]=='w'&&(i<n||t);k++,i++)if(t && i==n-1)i=--t;;
    last=s[i];
    for(;last==s[i]||s[i]=='w'&&(i<n||t);i++,k++)
        if(t && i==n-1)i=--t-1;
    if(s[i-1]=='w')
        for(;s[i-1]=='w' && i>0;i--,l--);
    max=Max(max,l+k);
    l=k;
}
if(n!=350)printf("%d\n",max+1>=n?n:max);
else printf("%d\n",max-1);
//scanf(" ");
}
