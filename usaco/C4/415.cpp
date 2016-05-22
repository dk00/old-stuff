#include<stdio.h>
#include<stdlib.h>
int pn,qn,stt[100000],len[100000],s[125001],num[125001];
main(){
int i,j,k,l,m,n,d,max;
scanf("%d %d",&n,&m);
max=m*m*2;
for(i=0;i<=m;i++)
    for(j=0;j<=i;j++)
        s[i*i+j*j]=1;
for(i=0;i<=max;i++)
    if(s[i])num[pn++]=i;
for(i=0;i<pn;i++)
    for(j=i+1;j<pn;j++){
        for(l=2,d=num[j]-num[i],k=num[j]+d;l<=n && s[k];k+=d)l++;
        if(l==n){
            stt[qn]=num[i];
            len[qn++]=d;
        }
    }
while(qn--)
    printf("%d %d\n",stt[qn],len[qn]);
scanf(" ");
}
