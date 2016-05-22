/*
ID: s0000151
PROG: fence6
LANG: C++
*/
#include<stdio.h>
int fen[100][100],v[100][100],link[100][100];
main(){
freopen("fence6.in","r",stdin);
freopen("fence6.out","w",stdout);
int i,j,k,l,n,u,p1[100],p2[100],len,l1,l2,is;
scanf("%d",&n);
for(u=i=0;i<n;i++)
    for(j=0;j<n;j++)fen[i][j]=10000000;
for(u=i=0;i<n;i++){
    scanf("%d",&i);--i;
    scanf("%d",&len);
    for(j=0;j<n;j++)p1[j]=p2[j]=0;
    scanf("%d %d",&j,&k);
    while(j--){
        scanf("%d",&l);
        p1[l-1]=1;
    }
    while(k--){
        scanf("%d",&l);
        p2[l-1]=1;
    }
    p1[i]=p2[i]=1;
    for(j=0;j<u;j++){
        for(is=1,k=0;k<n;k++)if(p1[k]!=v[j][k])is=0;
        if(is){l1=j;break;}
    }
    if(j>=u){
        l1=u++;
        for(k=0;k<n;k++)v[l1][k]=p1[k];
    }
    for(j=0;j<u;j++){
        for(is=1,k=0;k<n;k++)if(p2[k]!=v[j][k])is=0;
        if(is){l2=j;break;}
    }
    if(j>=u){
        l2=u++;
        for(k=0;k<n;k++)v[l2][k]=p2[k];
    }
    fen[l1][l2]=fen[l2][l1]=len;
    link[l1][l2]=link[l2][l1]=1;
}

for(k=0;k<u;k++)
    for(i=0;i<u;i++)
        for(j=0;j<u;j++)
            if(i!=j)fen[i][j]<?=(fen[i][k]+fen[k][j]);
for(is=10000000,l=0;l<u;l++)
    for(k=0;k<u;k++)
        for(i=0;i<u;i++)
            for(j=0;j<u;j++)
                if(link[i][j])
                    is<?=(fen[l][i]+fen[i][j]+fen[j][k]+fen[k][l]);
printf("%d\n",l);
}
