/*
ID: s0000151
PROG: nuggets
LANG: C++
*/
#include<stdio.h>
#define DEBUG 0
int n,s[10],p[1000000];
main(){
if(!DEBUG){freopen("nuggets.in","r",stdin);
freopen("nuggets.out","w",stdout);}
int i,k,one,odd,even,con,max=0;
scanf("%d",&n);
for(odd=even=one=i=0;i<n;i++){
    scanf("%d",&s[i]);
    for(k=0;i<i;k++){
        if(s[k]%s[i]==0){s[k]=s[i];n--;i--;break;}
        if(s[i]%s[k]==0){n--;i--;break;}
    }
    if(s[i]==1)one=1;
    p[s[i]]=1;
    if(s[i]%2)odd=1;
    else even=1;
}
if(one || odd+even==1){puts("0");return 0;}
for(i=0;i<n;i++)
    for(k=1;k<n;k++)
        if(s[k]<s[k-1]){
            con=s[k];s[k]=s[k-1];s[k-1]=con;
        }
for(con=k=0;k<1000000 && con<s[0];k++){
    if(p[k]){
        for(i=0;i<n;i++)if(s[i]+k<1000000)p[s[i]+k]=1;
        con++;
    }
    else{
        max=k;
        con=0;
    }
}
printf("%d\n",max);
if(DEBUG)scanf(" ");
}
